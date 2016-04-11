/*
 * WINNT POSIX Library
 * Version:  1.0
 * 
 * Copyright (C) 2002  Andrew Gnezdilov avi@risp.ru  All Rights Reserved.
 *
 * WINNT POSIX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * WINNT POSIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WINNT POSIX; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _MATHDEF_
#define _MATHDEF_

#if !defined _MATH_ && !defined _COMPLEX_
# error "Never use <pvt/mathdef.h> directly; include <math.h> instead"
#endif

#if defined __USE_UNIX98 && defined _MATH_
/* The ix87 FPUs evaluate all values in the 80 bit floating-point format
   which is also available for the user as `long double'.  Therefore we
   define:  */
typedef long double float_t;  /* `float' expressions are evaluated as
           `long double'.  */
typedef long double double_t; /* `double' expressions are evaluated as
           `long double'.  */

/* Signal that both types are `long double'.  */
# define FLT_EVAL_METHOD  2

/* Define `INFINITY' as value of type `float'.  */
# define INFINITY HUGE_VALF

/* The values returned by `ilogb' for 0 and NaN respectively.  */
# define FP_ILOGB0  0x80000000
# define FP_ILOGBNAN  0x80000000

/* Number of decimal digits for the `long double' type.  */
# define DECIMAL_DIG  18

#endif  /* ISO C 9X */

#endif /*mathdef.h */
