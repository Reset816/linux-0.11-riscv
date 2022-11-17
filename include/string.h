#ifndef _STRING_H_
#define _STRING_H_

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

extern char * strerror(int errno);

/*
 * This string-include defines all string functions as inline
 * functions. Use gcc. It also assumes ds=es=data space, this should be
 * normal. Most of the string-functions are rather heavily hand-optimized,
 * see especially strtok,strstr,str[c]spn. They should work, but are not
 * very easy to understand. Everything is done entirely within the register
 * set, making the functions fast and clean. String instructions have been
 * used through-out, making for "slightly" unclear code :-)
 *
 *		(C) 1991 Linus Torvalds
 */
 
static inline char * strcpy(char *dst, const char *src)
{
	char *ret = dst;

	while ((*dst++ = *src++));
	return ret;
}

static inline char * strncpy(char *dst, const char *src, size_t size)
{
	size_t len;

	for (len = 0; len < size; len++)
			if ((dst[len] = *src))
					src++;
	return dst;
}

static inline char * strcat(char *dest, const char *src)
{
    char *ret = dest;
    while (*dest)
        dest++;
    while (*dest++ = *src++)
        ;
    return ret;
}

static inline char * strncat(char *dst, const char *src, int size)
{
	char *orig = dst;

	while (*dst)
			dst++;

	while (size && (*dst = *src)) {
			src++;
			dst++;
			size--;
	}

	*dst = 0;
	return orig;
}

static inline int strcmp(const char *a, const char *b)
{
	unsigned int c;
	int diff;

	while (!(diff = (unsigned char)*a++ - (c = (unsigned char)*b++)) && c)
			;
	return diff;
}

static inline int strncmp(const char *a, const char *b, size_t size)
{
	unsigned int c;
	int diff = 0;

	while (size-- &&
			!(diff = (unsigned char)*a++ - (c = (unsigned char)*b++)) && c)
			;

	return diff;
}

static inline char * strchr(const char *s, int c)
{
	while (*s) {
			if (*s == (char)c)
					return (char *)s;
			s++;
	}
	return NULL;
}

static inline char * strrchr(const char *s, int c)
{
	const char *ret = NULL;

	while (*s) {
			if (*s == (char)c)
					ret = s;
			s++;
	}
	return (char *)ret;
}

static inline int strspn(const char *s1, const char *s2)
{
    size_t ret=0;
    while(*s1 && strchr(s2,*s1++))
        ret++;
    return ret;    
}

static inline int strcspn(const char *s1, const char *s2)
{
    size_t ret=0;
    while(*s1)
        if(strchr(s2,*s1))
            return ret;
        else
            s1++,ret++;
    return ret;
}

static inline char * strpbrk(const char *s1, const char *s2)
{
    while(*s1)
        if(strchr(s2, *s1++))
            return (char*)--s1;
    return 0;
}

static inline char * strstr(const char* string, const char* substring)
{
	const char *a, *b;
	b = substring;

	if(*b == 0)
		return (char*)string;
	
	for(; *string != 0; string += 1){
		if(*string != *b)
			continue;

		a = string;

		while(1){
			if(*b == 0)
				return (char*)string;
			if(*a++ != *b++)
				break;
		}

		b = substring;
	}

	return NULL;
}

static inline int strlen(const char *str)
{
	size_t len;

	for (len = 0; str[len]; len++);
	return len;
}

extern char * ___strtok;

static inline char * strtok(char * str, const char * delim)
{
    static char* p=0;
    if(str)
        p=str;
    else if(!p)
        return 0;
    str=p+strspn(p,delim);
    p=str+strcspn(str,delim);
    if(p==str)
        return p=0;
    p = *p ? *p=0,p+1 : 0;
    return str;
}

static inline void * memcpy(void *dst, const void *src, size_t len)
{
	size_t pos = 0;

	while (pos < len) {
			((char *)dst)[pos] = ((const char *)src)[pos];
			pos++;
	}
	return dst;
}

static inline void * memmove(void *dst, const void *src, size_t len)
{
	size_t dir, pos;

	pos = len;
	dir = -1;

	if (dst < src) {
			pos = -1;
			dir = 1;
	}

	while (len) {
			pos += dir;
			((char *)dst)[pos] = ((const char *)src)[pos];
			len--;
	}
	return dst;
}

static inline int memcmp(const void *s1, const void *s2, size_t n)
{
	size_t ofs = 0;
	char c1 = 0;

	while (ofs < n && !(c1 = ((char *)s1)[ofs] - ((char *)s2)[ofs])) {
			ofs++;
	}
	return c1;
}

static inline void * memchr(const void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char*)s;
    while( n-- )
        if( *p != (unsigned char)c )
            p++;
        else
            return p;
    return 0;
}

static inline void * memset(void *dst, int b, size_t len)
{
	char *p = dst;

	while (len--)
			*(p++) = b;
	return dst;
}

#endif
