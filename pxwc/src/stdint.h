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

#ifndef __PXWC_STD_INT_H__
#define __PXWC_STD_INT_H__

/* types for compat. with various BSD and other library sources */
typedef signed char      int8_t;
typedef unsigned char  u_int8_t;
typedef short            int16_t;
typedef unsigned short u_int16_t;
typedef int              int32_t;
typedef unsigned int   u_int32_t;

/* types for compat. with Solaris 7 */
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

/*
 * 64bit type for BSD compatability
 */
#ifdef __GNUC__
typedef long long int         quad_t;
typedef unsigned long long int  u_quad_t;
typedef unsigned long long int  uquad_t;
typedef long long int             int64_t;
typedef unsigned long long int  u_int64_t;
typedef unsigned long long int  uint64_t;
#elif _MSC_VER
typedef __int64           quad_t;
typedef unsigned __int64    u_quad_t;
typedef unsigned __int64    uquad_t;
typedef __int64           int64_t;
typedef unsigned __int64    u_int64_t;
typedef unsigned __int64    uint64_t;
#endif /*__GNUC__*/

#endif