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

#ifndef _MATH_
# error "Never use <bits/huge.h> directly; include <math.h> instead."
#endif

/* IEEE positive infinity (-HUGE_VAL is negative infinity).  */
extern double __inf_val;
#define HUGE_VAL __inf_val


/* ISO C 9X extensions: (float) HUGE_VALF and (long double) HUGE_VALL.  */

#ifdef __USE_UNIX98

extern float __finf_val;
# define HUGE_VALF __finf_val

extern long double __linf_val;
# define HUGE_VALL __linf_val

#endif  /* __USE_UNIX98.  */
