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

#if !defined _SIGNAL_ && !defined _SYSUCONTEXT_ && !defined _PSXSYS_ && !defined _TIME_
# error "Never use <bits/sigevent.h> directly; include <signal.h> instead."
#endif


#ifndef __have_sigevent_t
# define __have_sigevent_t

/* Structure to transport application-defined values with signals.  */

/* Forward declaration of the `pthread_attr_t' type.  */
# ifndef __pthread_attr_t_defined
typedef struct _THREAD_ATTRIBUTES pthread_attr_t;
#  define __pthread_attr_t_defined
# endif

typedef struct sigevent {
  sigval_t sigev_value;
  int sigev_signo;
  int sigev_notify;
  void (*sigev_notify_function) (sigval_t); /* Function to start.  */
  pthread_attr_t *sigev_notify_attributes;
} sigevent_t;

/* `sigev_notify' values.  */
/* Notify via signal.  */
# define SIGEV_SIGNAL 0
/* Other notification: meaningless.  */
# define SIGEV_NONE   1
/* Deliver via thread creation.  */
# define SIGEV_THREAD 2

#endif
