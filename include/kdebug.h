#ifndef __KDEBUG_H__
#define __KDEBUG_H__

#include <stdarg.h>
#include <stddef.h>
#include <sbi.h>

int sbiputs(const char *msg);
int sbiprintf(const char *fmt, ...);
void sbiputchar(char ch);

#endif
