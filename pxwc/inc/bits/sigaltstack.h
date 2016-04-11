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
# error "Never use <bits/sigaltstack.h> directly; include <signal.h> instead."
#endif

/* Alternate, preferred interface.  */
#ifndef __sigaltstack_defined
# define __sigaltstack_defined

typedef struct sigaltstack {
  void *ss_sp;
  int ss_size;
  int ss_flags;
} stack_t;

/* Possible values for `ss_flags.'.  */
# define SS_ONSTACK 0x0001
# define SS_DISABLE 0x0004

/* Minumum stack size for a signal handler.  */
# define MINSIGSTKSZ 8096

/* System default stack size.  */
# define SIGSTKSZ (MINSIGSTKSZ * 4)
#endif
