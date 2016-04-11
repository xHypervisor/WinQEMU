 /**************************************************************************\
 *                                                                          *
 *   pxwc - wgcc's gcc to cl libc wrapper                                   *
 *   Copyright (C) 2006  Markus Duft <markus.duft@salomon.at>               *
 *                                                                          *
 *   This library is free software; you can redistribute it and/or          *
 *   modify it under the terms of the GNU Lesser General Public             *
 *   License as published by the Free Software Foundation; either           *
 *   version 2.1 of the License, or (at your option) any later version.     *
 *                                                                          *
 *   This library is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *   Lesser General Public License for more details.                        *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with this library; if not, write to the Free Software    *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,             *
 *   MA  02110-1301 USA                                                     *
 *                                                                          *
 \**************************************************************************/

#ifndef _WIN32
#error This unistd.h is intended for use on Windows only!
#endif

#ifndef __PXWC_UNISTD_H__
#define __PXWC_UNISTD_H__

#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#endif
