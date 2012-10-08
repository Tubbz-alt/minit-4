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
** platform.h
**
**        Created on: Aug 08, 2012
**   Original Author: Sylvain Fargier <sylvain.fargier@somfy.com>
**
*/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(HAVE_LIBOWFAT)

#include <libowfat/fmt.h>
#include <libowfat/str.h>
#include <libowfat/buffer.h>
#include <libowfat/errmsg.h>
#include <libowfat/scan.h>
#include <libowfat/byte.h>

#else

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

#define buffer_2 stderr
#define buffer_1 stdout

typedef FILE buffer;
#define buffer_puts(b, msg) fputs(msg, b)
#define buffer_put(b, msg, len) fwrite(msg, 1, len, b)

#define buffer_putsflush buffer_puts
#define buffer_putflush buffer_put

#define buffer_flush(b) fflush(b)

#define str_len strlen

#define str_equal(s1, s2) (strcmp(s1, s2) == 0)

#define str_start(str, start) (strncmp(str, start, str_len(start)) == 0)

/* strchrnul could have do the job but it's a GNU extension */
size_t str_chr(const char *haystack, char needle);

void errmsg_iam(const char *name);
void errmsg_write(FILE *f, char perr, ...);

#define errmsg_warn(...) errmsg_write(stderr, 0, __VA_ARGS__)
#define errmsg_warnsys(...) errmsg_write(stderr, 1, __VA_ARGS__)
#define errmsg_info(...) errmsg_write(stdout, 0, __VA_ARGS__)
#define errmsg_infosys(...) errmsg_write(stdout, 1, __VA_ARGS__)

#define carp(...) errmsg_warn(__VA_ARGS__,(char*)0)
#define carpsys(...) errmsg_warnsys(__VA_ARGS__,(char*)0)
#define die(n,...) do { errmsg_warn(__VA_ARGS__,(char*)0); exit(n); } while (0)
#define diesys(n,...) do { errmsg_warnsys(__VA_ARGS__,(char*)0); exit(n); } while (0)
#define msg(...) errmsg_info(__VA_ARGS__,(char*)0);
#define msgsys(...) errmsg_infosys(__VA_ARGS__,(char*)0);

size_t fmt_ulong(char *dest, unsigned long src);
size_t fmt_str(char *dest, const char *src);

size_t scan_ulong(const char *src, unsigned long *dest);

int byte_equal(const char *a, size_t n, const char *b);

#define FMT_ULONG 40

#endif

#endif

