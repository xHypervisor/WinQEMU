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

#if defined _SYS_TYPES_ || defined _BITS_TYPES_ || defined _INTERNAL_ || defined _PSXSYS_
#ifndef _PTHREAD_TYPES_
#define _PTHREAD_TYPES_

#include <sched.h>

#ifdef _WIN64
# pragma pack (push, 8)
#else
# pragma pack (push, 4)
#endif

#if defined _INTERNAL_ || defined _PSXSYS_

typedef unsigned long PTHREAD;
typedef PTHREAD *PPTHREAD;
typedef struct _THREAD_ATTRIBUTES THREAD_ATTRIBUTES, *PTHREAD_ATTRIBUTES;
typedef const struct _THREAD_ATTRIBUTES *PCTHREAD_ATTRIBUTES;

typedef struct _MUTANT MUTANT, *PMUTANT;
typedef struct _MUTANT_ATTRIBUTES MUTANT_ATTRIBUTES, *PMUTANT_ATTRIBUTES;
typedef const struct _MUTANT_ATTRIBUTES *PCMUTANT_ATTRIBUTES;

typedef struct _CONDITION CONDITION, *PCONDITION;
typedef struct _CONDITION_ATTRIBUTES CONDITION_ATTRIBUTES, *PCONDITION_ATTRIBUTES;
typedef const struct _CONDITION_ATTRIBUTES *PCCONDITION_ATTRIBUTES;

typedef struct _ONCE_CONTROL ONCE_CONTROL, *PONCE_CONTROL;

typedef struct _RWLOCK RWLOCK, *PRWLOCK;
typedef struct _RWLOCK_ATTRIBUTES RWLOCK_ATTRIBUTES, *PRWLOCK_ATTRIBUTES;
typedef const struct _RWLOCK_ATTRIBUTES *PCRWLOCK_ATTRIBUTES;

typedef struct _SPIN SPIN, *PSPIN;

typedef struct _BARRIER BARRIER, *PBARRIER;
typedef struct _BARRIER_ATTRIBUTES BARRIER_ATTRIBUTES, *PBARRIER_ATTRIBUTES;
typedef const struct _BARRIER_ATTRIBUTES *PCBARRIER_ATTRIBUTES;

typedef struct _SEMAPHORE SEMAPHORE, *PSEMAPHORE;

#define UNINITIALIZED_OBJECT ((PVOID)-1)
#endif

struct _THREAD_ATTRIBUTES {
  int detach_state;
  int sched_policy;
  struct sched_param sched_param;
  int inherit_sched;
  int scope;
  size_t guard_size;
  void* stack_address; /* default NULL */
  size_t stack_size;
  void *np_security_descriptor;
  unsigned char np_inherit_handle;
};

struct _MUTANT {
/* 0*/  long int acquire_count;
/* 4*/  long int spinning_count;
/* 8*/  long int release_count;
/* C*/  void* lock_object;
/*10*/  long int recursion_count;
/*14*/  void* owning_thread; /* from the thread's ClientId->UniqueThread */
/*18*/  void *release_object;
/*1C*/  long int flags;
};

struct _MUTANT_ATTRIBUTES {
  unsigned int flags;
  int reserved;
};

struct _CONDITION {
  void* lock_object;
};

struct _CONDITION_ATTRIBUTES {
  unsigned int flags;
  int reserved;
};

struct _ONCE_CONTROL {
  int state;
  pid_t pid;
  void *done_object;
  unsigned long owner;
};

struct _SPIN {
/* 0*/  long int acquire_count;
/* 4*/  long int spinning_count;
/* 8*/  long int release_count;
/* C*/  void *lock_object;
/*10*/  void *release_object;
};

struct _RWLOCK {
/* 0*/  long int acquire_count;
/* 4*/  long int spinning_count;
/* 8*/  long int reserved;
/* C*/  void *lock_object;
/*10*/  long int number_active; // == 0 free, < 0 write, > 0 read
/*14*/  long int write_waiters;
/*18*/  long int read_waiters;
/*1C*/  void* owning_thread;
/*20*/  void* write_object;
/*24*/  void* read_object;
};

struct _RWLOCK_ATTRIBUTES {
  unsigned int flags;
  int reserved;
};

struct _BARRIER {
  void* lock_object;
};

struct _BARRIER_ATTRIBUTES {
  unsigned int flags;
  int reserved;
};

struct _SEMAPHORE {
  void* lock_object;
};

#pragma pack (pop)

#endif
#else
# error "Never use <bits/pthreadtypes.h> directly; include <sys/types.h> instead."
#endif
