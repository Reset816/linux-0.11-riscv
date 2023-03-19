#include <kdebug.h>
#include <sbi.h>
#include <stdarg.h>
#include <string.h>

static uint64_t sbipow(uint64_t x, uint64_t y);

void sbiputchar(char ch)
{
    sbi_console_putchar(ch);
}

int sbiputs(const char *msg)
{
    const char *ret = msg;
    for (; *msg != '\0'; ++msg) {
        sbiputchar(*msg);
    }
    sbiputchar('\n');
    return ret == msg;
}

int sbiprintf(const char *fmt, ...)
{
    va_list ap;
    uint64_t val;
    uint64_t temp;
    uint64_t len;
    uint64_t rev = 0;
    int ch;
    const char *str = NULL;

    va_start(ap, fmt);
    while (*fmt != '\0')
    {
        switch (*fmt)
        {
        case '%':
            fmt++;
            switch (*fmt)
            {
            case 'u':        //Decimal
                val = va_arg(ap, uint64_t);
                temp = val;
                len = 0;
                do
                {
                    len++;
                    temp /= 10;
                } while (temp);
                rev += len;
                temp = val;
                while (len)
                {
                    ch = temp / sbipow(10, len - 1);
                    temp %= sbipow(10, len - 1);
                    sbiputchar(ch + '0');
                    len--;
                }
                break;
            case 'p':
                sbiputchar('0');
                sbiputchar('x');
            case 'x':
                val = va_arg(ap, uint64_t);
                temp = val;
                len = 0;
                do
                {
                    len++;
                    temp /= 16;
                } while (temp);
                rev += len;
                temp = val;
                while (len)
                {
                    ch = temp / sbipow(16, len - 1);
                    temp %= sbipow(16, len - 1);
                    if (ch <= 9)
                    {
                        sbiputchar(ch + '0');
                    }
                    else
                    {
                        sbiputchar(ch - 10 + 'a');
                    }
                    len--;
                }
                break;
            case 's':
                str = va_arg(ap, const char*);

                while (*str)
                {
                    sbiputchar(*str);
                    str++;
                }
                break;
            case 'c':        //character
                sbiputchar(va_arg(ap, int));
                rev += 1;
                break;
            default:
                break;
            }
            break;
        case '\n':
            sbiputchar('\n');
            rev += 1;
            break;
        case '\r':
            sbiputchar('\r');
            rev += 1;
            break;
        case '\t':
            sbiputchar('\t');
            rev += 1;
            break;
        default:
            sbiputchar(*fmt);
        }
        fmt++;
    }
    va_end(ap);
    return rev;
}

static uint64_t sbipow(uint64_t x, uint64_t y)
{
    uint64_t sum = 1;
    while (y--) {
        sum *= x;
    }
    return sum;
}
