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

#if !defined _SCHED_ && !defined _PSXSYS_
# error "Never use <bits/scheddef.h> directly; include <sched.h> instead."
#endif

/*
 * NT use two schedulers Round robin for thread with priority from 1 to 15 and
 * second policy, Microsoft named it realtime, for threads with priority from 16 to 31.
 * Under second policy you must have the increase scheduling priority privilege to enter
 * the real-time range.
 */
#define SCHED_OTHER  0 /* for thread with kernel priority from 16 to 31 */
#define SCHED_FIFO   1 /* for thread with kernel priority from 1 to 15 */
#define SCHED_RR     2 /* unsupported */

#pragma pack (push, 4)

struct sched_param {
  int sched_priority;     /* Process execution scheduling priority */
  int reserved;
};

#pragma pack (pop)