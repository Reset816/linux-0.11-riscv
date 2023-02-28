#include "asm/dummy.h"

static inline unsigned char get_fs_byte(const char * addr)
{
	unsigned register char _v;

	DUMMY_ASM ("movb %%fs:%1,%0":"=r" (_v):"m" (*addr));
	return _v;
}

static inline unsigned short get_fs_word(const unsigned short *addr)
{
	unsigned short _v;

	DUMMY_ASM ("movw %%fs:%1,%0":"=r" (_v):"m" (*addr));
	return _v;
}

static inline unsigned long get_fs_long(const unsigned long *addr)
{
	unsigned long _v;

	DUMMY_ASM ("movl %%fs:%1,%0":"=r" (_v):"m" (*addr)); \
	return _v;
}

static inline void put_fs_byte(char val,char *addr)
{
DUMMY_ASM ("movb %0,%%fs:%1"::"r" (val),"m" (*addr));
}

static inline void put_fs_word(short val,short * addr)
{
DUMMY_ASM ("movw %0,%%fs:%1"::"r" (val),"m" (*addr));
}

static inline void put_fs_long(unsigned long val,unsigned long * addr)
{
DUMMY_ASM ("movl %0,%%fs:%1"::"r" (val),"m" (*addr));
}

/*
 * Someone who knows GNU asm better than I should double check the followig.
 * It seems to work, but I don't know if I'm doing something subtly wrong.
 * --- TYT, 11/24/91
 * [ nothing wrong here, Linus ]
 */

static inline unsigned long get_fs() 
{
	unsigned short _v;
	DUMMY_ASM("mov %%fs,%%ax":"=a" (_v):);
	return _v;
}

static inline unsigned long get_ds() 
{
	unsigned short _v;
	DUMMY_ASM("mov %%ds,%%ax":"=a" (_v):);
	return _v;
}

static inline void set_fs(unsigned long val)
{
	DUMMY_ASM("mov %0,%%fs"::"a" ((unsigned short) val));
}

