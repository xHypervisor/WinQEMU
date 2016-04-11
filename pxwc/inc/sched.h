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

#ifndef _SCHED_
#define _SCHED_

#include <features.h>

#define __need_timespec
#include <time.h>
#include <sys/types.h>

#ifndef __pid_t_defined
typedef long int pid_t;
# define __pid_t_defined
#endif

__BEGIN_DECLS

#include <bits/scheddef.h>

/* Set scheduling parameters for a process.  */
EXTERNAPI int sched_setparam (
  pid_t pid,
  const struct sched_param *param
);

/* Retrieve scheduling parameters for a particular process.  */
EXTERNAPI int sched_getparam (
  pid_t pid,
  struct sched_param *param
);

/* Set scheduling algorithm and/or parameters for a process.  */
EXTERNAPI int sched_setscheduler (
  pid_t pid,
  int policy,
  const struct sched_param *param
);

/* Retrieve scheduling algorithm for a particular purpose.  */
EXTERNAPI int sched_getscheduler (
  pid_t pid
);

/* Yield the processor.  */
EXTERNAPI int sched_yield (
  void
);

/* Get maximum priority value for a scheduler.  */
EXTERNAPI int sched_get_priority_max (
  int algorithm
);

/* Get minimum priority value for a scheduler.  */
EXTERNAPI int sched_get_priority_min (
  int algorithm
);

/* Get the SCHED_RR interval for the named process.  */
EXTERNAPI int sched_rr_get_interval (
  pid_t pid,
  struct timespec *tm
);

__END_DECLS

#endif // _SCHED_
