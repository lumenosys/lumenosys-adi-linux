#include <linux/module.h>

extern void dump_thread(struct pt_regs *, struct user *);

/* platform dependent support */

EXPORT_SYMBOL(__ioremap);
EXPORT_SYMBOL(iounmap);
EXPORT_SYMBOL(dump_thread);
EXPORT_SYMBOL(strnlen);
EXPORT_SYMBOL(strrchr);
EXPORT_SYMBOL(strstr);
EXPORT_SYMBOL(strchr);
EXPORT_SYMBOL(strcat);
EXPORT_SYMBOL(strlen);
EXPORT_SYMBOL(strcmp);
EXPORT_SYMBOL(strncmp);

EXPORT_SYMBOL(ip_fast_csum);

EXPORT_SYMBOL(enable_irq);
EXPORT_SYMBOL(disable_irq);
EXPORT_SYMBOL(kernel_thread);

/* Networking helper routines. */
EXPORT_SYMBOL(csum_partial_copy);

/* The following are special because they're not called
   explicitly (the C compiler generates them).  Fortunately,
   their interface isn't gonna change any time soon now, so
   it's OK to leave it out of version control.  */
EXPORT_SYMBOL_NOVERS(memcpy);
EXPORT_SYMBOL_NOVERS(memset);
EXPORT_SYMBOL_NOVERS(memcmp);
EXPORT_SYMBOL_NOVERS(memscan);
EXPORT_SYMBOL_NOVERS(memmove);
EXPORT_SYMBOL_NOVERS(memchr);

EXPORT_SYMBOL(get_wchan);

/*
 * libgcc functions - functions that are used internally by the
 * compiler...  (prototypes are not correct though, but that
 * doesn't really matter since they're not versioned).
 */
extern void __ashldi3(void);
extern void __ashrdi3(void);
extern void __divsi3(void);
extern void __lshrdi3(void);
extern void __modsi3(void);
extern void __muldi3(void);
extern void __udivsi3(void);
extern void __umodsi3(void);

/* gcc lib functions */
EXPORT_SYMBOL_NOVERS(__ashldi3);
EXPORT_SYMBOL_NOVERS(__ashrdi3);
EXPORT_SYMBOL_NOVERS(__divsi3);
EXPORT_SYMBOL_NOVERS(__lshrdi3);
EXPORT_SYMBOL_NOVERS(__modsi3);
EXPORT_SYMBOL_NOVERS(__muldi3);
EXPORT_SYMBOL_NOVERS(__udivsi3);
EXPORT_SYMBOL_NOVERS(__umodsi3);
