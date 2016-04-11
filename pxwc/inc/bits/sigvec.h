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

#if !defined _SIGNAL_ && !defined _SYSUCONTEXT_ && !defined _PSXSYS_
# error "Never use <bits/sigvec.h> directly; include <signal.h> instead."
#endif

#ifndef __have_sigvec_t
# define __have_sigvec_t

/* Structure passed to `sigvec'.  */
struct sigvec {
  void (*sv_handler) (int); /* Signal handler.  */
  int sv_mask;		/* Mask of signals to be blocked.  */

# if !defined (__GNUC__) || defined (__cplusplus)
  union {
    int sv_flags; /* Flags (see below). */
    int sv_onstack; /* 4.2 BSD compatibility. */
  };
# else
  int sv_flags; /* Flags (see below). */
#  define sv_onstack sv_flags /* 4.2 BSD compatibility. */
# endif
};

/* Bits in `sv_flags'.  */
# define SV_ONSTACK   0x008 /* Take the signal on the signal stack.  */
# define SV_INTERRUPT 0x080 /* Do not restart system calls.  */
# define SV_RESETHAND 0x10000000 /* Reset handler to SIG_DFL on receipt.  */

#endif