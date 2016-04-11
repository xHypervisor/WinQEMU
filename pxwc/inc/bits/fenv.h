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

#ifndef _FENV_
# error "Never use <bits/fenv.h> directly; include <fenv.h> instead."
#endif


/* Define bits representing the exception.  We use the bit positions
   of the appropriate bits in the FPU control word.  */
#define FE_INVALID 0x01
#define __FE_DENORM 0x02,
#define FE_DIVBYZERO 0x04
#define FE_OVERFLOW 0x08
#define FE_UNDERFLOW 0x10
#define FE_INEXACT 0x20

#define FE_ALL_EXCEPT \
  (FE_INEXACT | FE_DIVBYZERO | FE_UNDERFLOW | FE_OVERFLOW | FE_INVALID)

/* The ix87 FPU supports all of the four defined rounding modes.  We
   use again the bit positions in the FPU control word as the values
   for the appropriate macros.  */
#define FE_TONEAREST 0
#define FE_DOWNWARD 0x400
#define FE_UPWARD 0x800
#define FE_TOWARDZERO 0xc00

#define FE_LDBLPREC   0x00000300
#define FE_DBLPREC    0x00000200
#define FE_FLTPREC    0x00000000

/* Type representing exception flags.  */
typedef unsigned short fexcept_t;
typedef struct {
  unsigned short control;
  unsigned short status;
  unsigned int   eip;
  unsigned short cs_selector;
  unsigned short opcode;
  unsigned int   data_offset;
  unsigned short data_selector;
} fenv_t;

/* If the default argument is used we use this value.  */
#define FE_DFL_ENV  ((fenv_t *) -1)

#ifdef __USE_GNU
/* Floating-point environment where none of the exception is masked.  */
# define FE_NOMASK_ENV  ((fenv_t *) -2)
#endif
