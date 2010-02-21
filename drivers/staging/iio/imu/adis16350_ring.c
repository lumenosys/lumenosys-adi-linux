#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/workqueue.h>
#include <linux/mutex.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/sysfs.h>
#include <linux/list.h>

#include "../iio.h"
#include "../sysfs.h"
#include "../ring_sw.h"
#include "../accel/accel.h"
#include "../trigger.h"
#include "adis16350.h"

/**
 * combine_8_to_16() utility function to munge to u8s into u16
 **/
static inline u16 combine_8_to_16(u8 lower, u8 upper)
{
	u16 _lower = lower;
	u16 _upper = upper;
	return _lower | (_upper << 8);
}

static IIO_SCAN_EL_C(supply, ADIS16350_SCAN_SUPPLY, IIO_SIGNED(14),
		     ADIS16350_SUPPLY_OUT, NULL);

static IIO_SCAN_EL_C(gyro_x, ADIS16350_SCAN_GYRO_X, IIO_SIGNED(14),
		     ADIS16350_XGYRO_OUT, NULL);
static IIO_SCAN_EL_C(gyro_y, ADIS16350_SCAN_GYRO_Y, IIO_SIGNED(14),
		     ADIS16350_YGYRO_OUT, NULL);
static IIO_SCAN_EL_C(gyro_z, ADIS16350_SCAN_GYRO_Z, IIO_SIGNED(14),
		     ADIS16350_ZGYRO_OUT, NULL);

static IIO_SCAN_EL_C(accel_x, ADIS16350_SCAN_ACC_X, IIO_SIGNED(14),
		     ADIS16350_XACCL_OUT, NULL);
static IIO_SCAN_EL_C(accel_y, ADIS16350_SCAN_ACC_Y, IIO_SIGNED(14),
		     ADIS16350_YACCL_OUT, NULL);
static IIO_SCAN_EL_C(accel_z, ADIS16350_SCAN_ACC_Z, IIO_SIGNED(14),
		     ADIS16350_ZACCL_OUT, NULL);

static IIO_SCAN_EL_C(temp_x, ADIS16350_SCAN_TEMP_X, IIO_SIGNED(14),
		     ADIS16350_XTEMP_OUT, NULL);
static IIO_SCAN_EL_C(temp_y, ADIS16350_SCAN_TEMP_Y, IIO_SIGNED(14),
		     ADIS16350_YTEMP_OUT, NULL);
static IIO_SCAN_EL_C(temp_z, ADIS16350_SCAN_TEMP_Z, IIO_SIGNED(14),
		     ADIS16350_ZTEMP_OUT, NULL);

static IIO_SCAN_EL_C(adc_0, ADIS16350_SCAN_ADC_0, IIO_SIGNED(12),
		     ADIS16350_AUX_ADC, NULL);

static IIO_SCAN_EL_TIMESTAMP;

static struct attribute *adis16350_scan_el_attrs[] = {
	&iio_scan_el_supply.dev_attr.attr,
	&iio_scan_el_gyro_x.dev_attr.attr,
	&iio_scan_el_gyro_y.dev_attr.attr,
	&iio_scan_el_gyro_z.dev_attr.attr,
	&iio_scan_el_accel_x.dev_attr.attr,
	&iio_scan_el_accel_y.dev_attr.attr,
	&iio_scan_el_accel_z.dev_attr.attr,
	&iio_scan_el_temp_x.dev_attr.attr,
	&iio_scan_el_temp_y.dev_attr.attr,
	&iio_scan_el_temp_z.dev_attr.attr,
	&iio_scan_el_adc_0.dev_attr.attr,
	&iio_scan_el_timestamp.dev_attr.attr,
	NULL,
};

static struct attribute_group adis16350_scan_el_group = {
	.attrs = adis16350_scan_el_attrs,
	.name = "scan_elements",
};

/**
 * adis16350_poll_func_th() top half interrupt handler called by trigger
 * @private_data:	iio_dev
 **/
static void adis16350_poll_func_th(struct iio_dev *indio_dev)
{
  struct adis16350_state *st = iio_dev_get_devdata(indio_dev);
	st->last_timestamp = indio_dev->trig->timestamp;
	schedule_work(&st->work_trigger_to_ring);
	/* Indicate that this interrupt is being handled */

	/* Technically this is trigger related, but without this
	 * handler running there is currently no way for the interrupt
	 * to clear.
	 */
}

/**
 * adis16350_read_data_from_ring() individual data elements read from ring
 **/
ssize_t adis16350_read_data_from_ring(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct iio_scan_el *el = NULL;
	int ret, len = 0, i = 0;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct iio_dev *dev_info = dev_get_drvdata(dev);
	s16 *data;

	while (dev_info->scan_el_attrs->attrs[i]) {
		el = to_iio_scan_el((struct device_attribute *)
				    (dev_info->scan_el_attrs->attrs[i]));
		/* label is in fact the address */
		if (el->label == this_attr->address)
			break;
		i++;
	}
	if (!dev_info->scan_el_attrs->attrs[i]) {
		ret = -EINVAL;
		goto error_ret;
	}
	/* If this element is in the scan mask */
	ret = iio_scan_mask_query(dev_info, el->number);
	if (ret < 0)
		goto error_ret;
	if (ret) {
		data = kmalloc(dev_info->ring->access.get_bpd(dev_info->ring),
			       GFP_KERNEL);
		if (data == NULL)
			return -ENOMEM;
		ret = dev_info->ring->access.read_last(dev_info->ring,
						      (u8 *)data);
		if (ret)
			goto error_free_data;
	} else {
		ret = -EINVAL;
		goto error_ret;
	}
	len = iio_scan_mask_count_to_right(dev_info, el->number);
	if (len < 0) {
		ret = len;
		goto error_free_data;
	}
	len = sprintf(buf, "ring %d\n", data[len]);
error_free_data:
	kfree(data);
error_ret:
	return ret ? ret : len;

}

/* Whilst this makes a lot of calls to iio_sw_ring functions - it is to device
 * specific to be rolled into the core.
 */
static void adis16350_trigger_bh_to_ring(struct work_struct *work_s)
{
	struct adis16350_state *st
		= container_of(work_s, struct adis16350_state,
			       work_trigger_to_ring);

	int i = 0;
	s16 *data;
	size_t datasize = st->indio_dev
		->ring->access.get_bpd(st->indio_dev->ring);

	data = kmalloc(datasize , GFP_KERNEL);
	if (data == NULL) {
		dev_err(&st->us->dev, "memory alloc failed in ring bh");
		return;
	}

	if (st->indio_dev->scan_count)
		if (adis16350_spi_read_burst(&st->indio_dev->dev, st->rx) >= 0)
			for (; i < st->indio_dev->scan_count; i++) {
				data[i] = combine_8_to_16(st->rx[i*2+1],
							  st->rx[i*2]);
			}

	/* Guaranteed to be aligned with 8 byte boundary */
	if (st->indio_dev->scan_timestamp)
		*((s64 *)(data + ((i + 3)/4)*4)) = st->last_timestamp;

	st->indio_dev->ring->access.store_to(st->indio_dev->ring,
					    (u8 *)data,
					    st->last_timestamp);

	iio_trigger_notify_done(st->indio_dev->trig);
	kfree(data);

	return;
}
/* in these circumstances is it better to go with unaligned packing and
 * deal with the cost?*/
static int adis16350_data_rdy_ring_preenable(struct iio_dev *indio_dev)
{
	size_t size;
	dev_dbg(&indio_dev->dev, "%s\n", __func__);
	/* Check if there are any scan elements enabled, if not fail*/
	if (!(indio_dev->scan_count || indio_dev->scan_timestamp))
		return -EINVAL;

	if (indio_dev->ring->access.set_bpd) {
		if (indio_dev->scan_timestamp)
			if (indio_dev->scan_count) /* Timestamp and data */
				size = 6*sizeof(s64);
			else /* Timestamp only  */
				size = sizeof(s64);
		else /* Data only */
			size = indio_dev->scan_count*sizeof(s16);
		indio_dev->ring->access.set_bpd(indio_dev->ring, size);
	}

	return 0;
}

static int adis16350_data_rdy_ring_postenable(struct iio_dev *indio_dev)
{
	return indio_dev->trig
		? iio_trigger_attach_poll_func(indio_dev->trig,
					       indio_dev->pollfunc)
		: 0;
}

static int adis16350_data_rdy_ring_predisable(struct iio_dev *indio_dev)
{
	return indio_dev->trig
		? iio_trigger_dettach_poll_func(indio_dev->trig,
						indio_dev->pollfunc)
		: 0;
}

void adis16350_unconfigure_ring(struct iio_dev *indio_dev)
{
	kfree(indio_dev->pollfunc);
	iio_sw_rb_free(indio_dev->ring);
}

int adis16350_configure_ring(struct iio_dev *indio_dev)
{
	int ret = 0;
	struct adis16350_state *st = indio_dev->dev_data;
	struct iio_ring_buffer *ring;
	INIT_WORK(&st->work_trigger_to_ring, adis16350_trigger_bh_to_ring);
	/* Set default scan mode */

	iio_scan_mask_set(indio_dev, iio_scan_el_supply.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_gyro_x.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_gyro_y.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_gyro_z.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_accel_x.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_accel_y.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_accel_z.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_temp_x.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_temp_y.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_temp_z.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_adc_0.number);
	indio_dev->scan_timestamp = true;

	indio_dev->scan_el_attrs = &adis16350_scan_el_group;

	ring = iio_sw_rb_allocate(indio_dev);
	if (!ring) {
		ret = -ENOMEM;
		return ret;
	}
	indio_dev->ring = ring;
	/* Effectively select the ring buffer implementation */
	iio_ring_sw_register_funcs(&ring->access);
	ring->preenable = &adis16350_data_rdy_ring_preenable;
	ring->postenable = &adis16350_data_rdy_ring_postenable;
	ring->predisable = &adis16350_data_rdy_ring_predisable;
	ring->owner = THIS_MODULE;

	indio_dev->pollfunc = kzalloc(sizeof(*indio_dev->pollfunc), GFP_KERNEL);
	if (indio_dev->pollfunc == NULL) {
		ret = -ENOMEM;
		goto error_iio_sw_rb_free;;
	}
	indio_dev->pollfunc->poll_func_main = &adis16350_poll_func_th;
	indio_dev->pollfunc->private_data = indio_dev;
	indio_dev->modes |= INDIO_RING_TRIGGERED;
	return 0;

error_iio_sw_rb_free:
	iio_sw_rb_free(indio_dev->ring);
	return ret;
}

int adis16350_initialize_ring(struct iio_ring_buffer *ring)
{
	return iio_ring_buffer_register(ring);
}

void adis16350_uninitialize_ring(struct iio_ring_buffer *ring)
{
	iio_ring_buffer_unregister(ring);
}
