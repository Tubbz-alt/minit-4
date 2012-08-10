/*
** Copyright (C) 2012 Fargier Sylvain <fargier.sylvain@free.fr>
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
** fmt_ulong.c
**
**        Created on: Aug 10, 2012
**   Original Author: Fargier Sylvain <fargier.sylvain@free.fr>
**
*/

#include "platform.h"

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

