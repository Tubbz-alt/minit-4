/*
** Copyright (C) 2012 Sylvain Fargier <sylvain.fargier@somfy.com>
**
** This software is provided 'as-is', without any express or implied
** warranty.  In no event will the authors be held liable for any damages
** arising from the use of this software.
**
** Permission is granted to anyone to use this software for any purpose,
** including commercial applications, and to alter it and redistribute it
** freely, subject to the following restrictions:
**
** 1. The origin of this software must not be misrepresented; you must not
**    claim that you wrote the original software. If you use this software
**    in a product, an acknowledgment in the product documentation would be
**    appreciated but is not required.
** 2. Altered source versions must be plainly marked as such, and must not be
**    misrepresented as being the original software.
** 3. This notice may not be removed or altered from any source distribution.
**
** platform.c
**
**        Created on: Aug 08, 2012
**   Original Author: Sylvain Fargier <sylvain.fargier@somfy.com>
**
*/

#if !defined(__dietlibc__)

#include <stdarg.h>
#include <errno.h>

#include "platform.h"

size_t str_chr(const char *haystack, char needle)
{
    register size_t i;

    for (i = 0; haystack[i] != '\0'; ++i)
        if (haystack[i] == needle)
            break;
    return i;
}

size_t fmt_ulong(char *dest, unsigned long src)
{
    char buff[FMT_ULONG];
    size_t pos = FMT_ULONG, ret;

    do {
        buff[--pos] = '0' + (src % 10);
    } while ((src /= 10) != 0);

    ret = FMT_ULONG - pos;
    if (dest)
        memcpy(dest, &buff[pos], ret);
    return ret;
}

size_t fmt_str(char *dest, const char *src)
{
    size_t ret = str_len(src);

    if (dest)
        memcpy(dest, src, ret);
    return ret;
}

/* different behavior form libowfat's, on overflow continue to process input */
size_t scan_ulong(const char *src, unsigned long int *dest) {
    register const char *tmp = src;
    register unsigned long int l = 0;
    register unsigned char c;

    while ((c = *(tmp) - '0') < 10) {
        l = (l << 3) + (l << 1) + c;
        ++tmp;
    }
    if (dest)
        *dest = l;
    return tmp - src;
}

static const char *argv0 = 0;

void errmsg_iam(const char *name)
{
    argv0 = name;
}

void errmsg_write(FILE *f, char perr, ...)
{
    if (argv0)
    {
        fputs(argv0, f);
        fputs(": ", f);
    }

    va_list a;
    va_start(a, perr);

    const char *s;
    while ((s = va_arg(a, const char *)) != 0)
    {
        fputs(s, f);
    }
    va_end(a);

    if (perr)
    {
        fputs(": ", f);
        fputs(strerror(errno), f);
    }

    fputs("\n", f);
}

int byte_equal(const char *a, size_t n, const char *b)
{
    while (n--)
        if (*(a++) != *(b++))
            return 0;
    return 1;
}

#endif

