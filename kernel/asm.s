/*
 *  linux/kernel/asm.s
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 * asm.s contains the low-level code for most hardware faults.
 * page_exception is handled by the mm, so that isn't here. This
 * file also handles (hopefully) fpu-exceptions due to TS-bit, as
 * the fpu must be properly saved/resored. This hasn't been tested.
 */

.globl divide_error,debug,nmi,int3,overflow,bounds,invalid_op
.globl double_fault,coprocessor_segment_overrun
.globl invalid_TSS,segment_not_present,stack_segment
.globl general_protection,coprocessor_error,irq13,reserved

divide_error:
	nop
	ret
no_error_code:
	nop
	ret

debug:
	nop

nmi:
	nop

int3:
	nop

overflow:
	nop

bounds:
	nop

invalid_op:
	nop

coprocessor_segment_overrun:
	nop

reserved:
	nop

irq13:
	nop

double_fault:
	nop
error_code:
	nop

invalid_TSS:
	nop

segment_not_present:
	nop

stack_segment:
	nop

general_protection:
	nop

