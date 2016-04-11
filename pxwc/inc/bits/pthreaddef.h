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

#if !defined _PTHREAD_ && !defined _PSXSYS_
# error "Never use <bits/pthreaddef.h> directly; include <pthread.h> instead."
#endif

#define PTHREAD_CREATE_JOINABLE           0x00000001
#define PTHREAD_CREATE_DETACHED           0x00000002

#define PTHREAD_INHERIT_SCHED             0x00000010
#define PTHREAD_EXPLICIT_SCHED            0x00000020

#define PTHREAD_SCOPE_SYSTEM              0x00000100
#define PTHREAD_SCOPE_PROCESS             0x00000200

#define PTHREAD_CANCEL_ENABLE 0x01000000
#define PTHREAD_CANCEL_DISABLE 0x02000000
#define PTHREAD_CANCEL_DEFERRED 0x04000000
#define PTHREAD_CANCEL_ASYNCHRONOUS 0x08000000
#define PTHREAD_CANCELED ((void*)-1)

#define PTHREAD_MUTEX_ADAPTIVE_NP         0x00001000
#ifdef __USE_GNU
# define PTHREAD_MUTEX_FAST_NP            0x00001000
#endif
#define PTHREAD_MUTEX_ERRORCHECK_NP       0x00002000
#define PTHREAD_MUTEX_RECURSIVE_NP        0x00004000

#if defined __USE_UNIX98
# define PTHREAD_MUTEX_NORMAL             0x00001000
# define PTHREAD_MUTEX_DEFAULT            0x00001000
# define PTHREAD_MUTEX_ERRORCHECK         0x00002000
# define PTHREAD_MUTEX_RECURSIVE          0x00004000
#endif

#define PTHREAD_PROCESS_SHARED            0x00010000
#define PTHREAD_PROCESS_PRIVATE           0x00020000

/* Initializers. */
#define PTHREAD_MUTEX_INITIALIZER \
  { -1, 1024, -1, (void*)-1, 0, NULL, (void*)-1, PTHREAD_MUTEX_DEFAULT | PTHREAD_PROCESS_PRIVATE }
#if defined __USE_GNU
# define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP PTHREAD_MUTEX_INITIALIZER
# define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
  { -1, 1024, -1, (void*)-1, 0, NULL, (void*)-1, PTHREAD_MUTEX_RECURSIVE_NP | PTHREAD_PROCESS_PRIVATE }
# define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP \
  { -1, 1024, -1, (void*)-1, 0, NULL, (void*)-1, PTHREAD_MUTEX_ERRORCHECK_NP | PTHREAD_PROCESS_PRIVATE }
#endif

#ifdef __USE_UNIX98
# define PTHREAD_RWLOCK_INITIALIZER \
  { -1, 512, 0, (void*)-1, 0, 0, 0, NULL, (void*)-1, (void*)-1 }
#endif

/*#ifdef __USE_UNIX98
# define PTHREAD_RWLOCK_PREFER_READER_NP 0x00100000
# define PTHREAD_RWLOCK_PREFER_WRITER_NP 0x00200000
# define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP 0x00400000
# define PTHREAD_RWLOCK_DEFAULT_NP PTHREAD_RWLOCK_PREFER_WRITER_NP
#endif	/* Unix98 */

#define PTHREAD_ONCE_INIT { 0, 0L, (void*)-1, (unsigned long int)-1 }

/* Special constants */

#ifdef __USE_XOPEN2K
/* -1 is distinct from 0 and all errno constants */
# define PTHREAD_BARRIER_SERIAL_THREAD -1
#endif

/* Cleanup buffers */

typedef struct _NTTH_CLEANUP_BUFFER NTTH_CLEANUP_BUFFER, *PNTTH_CLEANUP_BUFFER;
struct _NTTH_CLEANUP_BUFFER {
  PNTTH_CLEANUP_BUFFER prev; /* Chain */
  void *cleanup_handler; /* caller of the cleanup_routine */
  void (*cleanup_routine) (void *); /* Function to call.  */
  void *userarg; /* Its argument.  */
  int canceltype; /* Saved cancellation type. */
};
