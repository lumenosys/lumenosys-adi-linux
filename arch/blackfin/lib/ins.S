/*
 * arch/blackfin/lib/ins.S - ins{bwl} using hardware loops
 *
 * Copyright 2004-2008 Analog Devices Inc.
 * Copyright (C) 2005 Bas Vermeulen, BuyWays BV <bas@buyways.nl>
 * Licensed under the GPL-2 or later.
 */

#include <linux/linkage.h>
#include <asm/blackfin.h>

.align 2

/*
 * Reads on the Blackfin are speculative. In Blackfin terms, this means they
 * can be interrupted at any time (even after they have been issued on to the
 * external bus), and re-issued after the interrupt occurs.
 *
 * If a FIFO is sitting on the end of the read, it will see two reads,
 * when the core only sees one. The FIFO receives the read which is cancelled,
 * and not delivered to the core.
 *
 * To solve this, interrupts are turned off before reads occur to I/O space.
 * There are 3 versions of all these functions
 *  - turns interrupts off every read (higher overhead, but lower latency)
 *  - turns interrupts off every loop (low overhead, but longer latency)
 *  - DMA version, which do not suffer from this issue. DMA versions have
 *      different name (prefixed by dma_ ), and are located in
 *      ../kernel/bfin_dma_5xx.c
 * Using the dma related functions are recommended for transferring large
 * buffers in/out of FIFOs.
 * When the interrupt pipeline is enabled, a low overhead
 * version is always used, which still preserves low latency for the
 * real-time domain.
 */

#ifdef CONFIG_IPIPE

#define COMMON_INS(func, ops) \
ENTRY(_ins##func) \
	P0 = R0;	/* P0 = port */ \
	P1 = R1;	/* P1 = address */ \
	P2 = R2;	/* P2 = count */ \
	[--SP] = RETS; \
	[--SP] = (P5:0); \
	SP += -12; \
	CALL ___ipipe_hard_save_root_irqs; \
	SP += 12; \
	R3 = R0;\
	(P5:0) = [SP++];\
	SSYNC; \
	LSETUP(1f, 2f) LC0 = P2; \
1:	ops; \
2:	nop; \
	R0 = R3;\
	SP += -12; \
	CALL ___ipipe_hard_restore_root_irqs; \
	SP += 12; \
	RETS = [SP++];\
	RTS; \
ENDPROC(_ins##func)

#else /* !CONFIG_IPIPE */

# define DO_CLI cli R3;
# define CLI_INNER_NOP nop; nop; nop;
# define DO_STI 2: sti R3;

#ifdef CONFIG_BFIN_INS_LOWOVERHEAD
# define CLI_OUTER DO_CLI;
# define STI_OUTER DO_STI;
# define CLI_INNER 1:
# if ANOMALY_05000416
#  define STI_INNER nop; 2: nop;
# else
#  define STI_INNER 2:
# endif
#else
# define CLI_OUTER
# define STI_OUTER
# define CLI_INNER 1: DO_CLI; CLI_INNER_NOP;
# define STI_INNER DO_STI;
#endif

/*
 * Reads on the Blackfin are speculative. In Blackfin terms, this means they
 * can be interrupted at any time (even after they have been issued on to the
 * external bus), and re-issued after the interrupt occurs.
 *
 * If a FIFO is sitting on the end of the read, it will see two reads,
 * when the core only sees one. The FIFO receives the read which is cancelled,
 * and not delivered to the core.
 *
 * To solve this, interrupts are turned off before reads occur to I/O space.
 * There are 3 versions of all these functions
 *  - turns interrupts off every read (higher overhead, but lower latency)
 *  - turns interrupts off every loop (low overhead, but longer latency)
 *  - DMA version, which do not suffer from this issue. DMA versions have
 *      different name (prefixed by dma_ ), and are located in
 *      ../kernel/bfin_dma.c
 * Using the dma related functions are recommended for transferring large
 * buffers in/out of FIFOs.
 */

#define COMMON_INS(func, ops) \
ENTRY(_ins##func) \
	P0 = R0;	/* P0 = port */ \
	CLI_OUTER;	/* 3 instructions before first read access */ \
	P1 = R1;	/* P1 = address */ \
	P2 = R2;	/* P2 = count */ \
	SSYNC; \
 \
	LSETUP(1f, 2f) LC0 = P2; \
	CLI_INNER; \
	ops; \
	STI_INNER; \
 \
	STI_OUTER; \
	RTS; \
ENDPROC(_ins##func)

#endif /* !CONFIG_IPIPE */

COMMON_INS(l, \
	R0 = [P0]; \
	[P1++] = R0; \
)

COMMON_INS(w, \
	R0 = W[P0]; \
	W[P1++] = R0; \
)

COMMON_INS(w_8, \
	R0 = W[P0]; \
	B[P1++] = R0; \
	R0 = R0 >> 8; \
	B[P1++] = R0; \
)

COMMON_INS(b, \
	R0 = B[P0]; \
	B[P1++] = R0; \
)

COMMON_INS(l_16, \
	R0 = [P0]; \
	W[P1++] = R0; \
	R0 = R0 >> 16; \
	W[P1++] = R0; \
)
