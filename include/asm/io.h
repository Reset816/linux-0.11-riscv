#include "asm/dummy.h"

#define outb(value,port) \
DUMMY_ASM ("outb %%al,%%dx"::"a" (value),"d" (port))


#define inb(port) ({ \
unsigned char _v; \
DUMMY_ASM ("inb %%dx,%%al":"=a" (_v):"d" (port)); \
_v; \
})

#define outb_p(value,port) \
DUMMY_ASM ("outb %%al,%%dx\n" \
		"\tjmp 1f\n" \
		"1:\tjmp 1f\n" \
		"1:"::"a" (value),"d" (port))

#define inb_p(port) ({ \
unsigned char _v; \
DUMMY_ASM ("inb %%dx,%%al\n" \
	"\tjmp 1f\n" \
	"1:\tjmp 1f\n" \
	"1:":"=a" (_v):"d" (port)); \
_v; \
})
