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

#if !defined _PTHREAD_ && !defined _SIGNAL_ && !defined _SYSUCONTEXT_ && !defined _PSXSYS_
# error "Never use <bits/sigset.h> directly; include <signal.h> instead."
#endif

#define __TOTAL_SIGNAL_COUNT 256

#if defined _INTERNAL_ || defined _PSXSYS_
# define _MAXSIGNO (__TOTAL_SIGNAL_COUNT + 1)
# define _MAXSIGN  __TOTAL_SIGNAL_COUNT
#endif

/* A `sigset_t' has a bit for each signal.  */
#ifndef __sigset_t_defined
# define _SIGSET_NWORDS	(__TOTAL_SIGNAL_COUNT / (8 * sizeof (unsigned long int)))
typedef struct _sigset {
  unsigned long int __val[_SIGSET_NWORDS];
} sigset_t;
# define __sigset_t_defined
#endif

#ifdef __need_sigset_t
# undef __need_sigset_t
#endif
