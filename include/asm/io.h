#define outb(value,port) \
	*(volatile unsigned char *) (port) = (unsigned char) (value)

#define inb(port) ({ \
unsigned char _v; _v = *(volatile unsigned char *)(port); \
_v; \
})

#define outb_p(value,port) \
	*(volatile unsigned char *) (port) = (unsigned char) (value)

#define inb_p(port) ({ \
unsigned char _v; _v = *(volatile unsigned char *)(port); \
_v; \
})
