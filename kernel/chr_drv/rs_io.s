/*
 *  linux/kernel/rs_io.s
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 *	rs_io.s
 *
 * This module implements the rs232 io interrupts.
 */

.text
.globl rs1_interrupt,rs2_interrupt

size	= 1024				/* must be power of two !
					   and must match the value
					   in tty_io.c!!! */

/* these are the offsets into the read/write buffer structures */
rs_addr = 0
head = 4
tail = 8
proc_list = 12
buf = 16

startup	= 256		/* chars left in write queue when we restart it */

/*
 * These are the actual interrupt routines. They look where
 * the interrupt is coming from, and take appropriate action.
 */
.align 2
rs1_interrupt:
	nop
.align 2
rs2_interrupt:
	nop

jmp_table:
	.long modem_status,write_char,read_char,line_status

.align 2
modem_status:
	ret

.align 2
line_status:
	ret

.align 2
read_char:
	ret

.align 2
write_char:
	ret
.align 2
write_buffer_empty:
	nop
	ret
