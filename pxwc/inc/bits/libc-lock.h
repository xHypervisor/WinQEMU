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

#ifndef _BITS_LIBC_LOCK_
#define _BITS_LIBC_LOCK_

#include <pthread.h>

/* Mutex type.  */
#ifdef _LIBC
typedef pthread_mutex_t __libc_lock_t;
typedef pthread_rwlock_t __libc_rwlock_t;
#else
typedef struct __libc_lock_opaque__ __libc_lock_t;
typedef struct __libc_rwlock_opaque__ __libc_rwlock_t;
#endif

/* Type for key to thread-specific data.  */
typedef pthread_key_t __libc_key_t;

/* Define a lock variable NAME with storage class CLASS.  The lock must be
   initialized with __libc_lock_init before it can be used (or define it
   with __libc_lock_define_initialized, below).  Use `extern' for CLASS to
   declare a lock defined in another module.  In public structure
   definitions you must use a pointer to the lock structure (i.e., NAME
   begins with a `*'), because its storage size will not be known outside
   of libc.  */
#define __libc_lock_define(CLASS,NAME) \
  CLASS __libc_lock_t NAME;
#define __libc_rwlock_define(CLASS,NAME) \
  CLASS __libc_rwlock_t NAME;
#define __libc_lock_define_initialized(CLASS,NAME) \
  CLASS __libc_lock_t NAME = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP /*faster work */;
#define __libc_rwlock_define_initialized(CLASS,NAME) \
  CLASS __libc_rwlock_t NAME = PTHREAD_RWLOCK_INITIALIZER;

/* Define an initialized recursive lock variable NAME with storage
   class CLASS.  */
#define __libc_lock_define_initialized_recursive(CLASS,NAME) \
  CLASS __libc_lock_t NAME = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

/* Initialize the named lock variable, leaving it in a consistent, unlocked
   state.  */
extern __libc_mutex_init (pthread_mutex_t *mutex); /* initialize recursive mutex */
#define __libc_lock_init(NAME) __libc_mutex_init (&(NAME));
#define __libc_rwlock_init(NAME) pthread_rwlock_init (&(NAME), NULL);
/* Same as last but this time we initialize a recursive mutex.  */
#define __libc_lock_init_recursive(NAME) __libc_mutex_init (&(NAME));

/* Finalize the named lock variable, which must be locked.  It cannot be
   used again until __libc_lock_init is called again on it.  This must be
   called on a lock variable before the containing storage is reused.  */
#define __libc_lock_fini(NAME) pthread_mutex_destroy (&(NAME));
#define __libc_rwlock_fini(NAME) pthread_rwlock_destroy (&(NAME));

/* Finalize recursive named lock.  */
#define __libc_lock_fini_recursive(NAME) __libc_lock_fini (NAME)

/* Lock the named lock variable.  */
#define __libc_lock_lock(NAME) pthread_mutex_lock (&(NAME));
#define __libc_rwlock_rdlock(NAME) pthread_rwlock_rdlock (&(NAME));
#define __libc_rwlock_wrlock(NAME) pthread_rwlock_wrlock (&(NAME));

/* Lock the recursive named lock variable.  */
#define __libc_lock_lock_recursive(NAME) __libc_lock_lock (NAME)

/* Try to lock the named lock variable.  */
#define __libc_lock_trylock(NAME) pthread_mutex_trylock (&(NAME))
#define __libc_rwlock_tryrdlock(NAME) pthread_rwlock_tryrdlock (&(NAME))
#define __libc_rwlock_trywrlock(NAME) pthread_rwlock_trywrlock (&(NAME))

/* Try to lock the recursive named lock variable.  */
#define __libc_lock_trylock_recursive(NAME) __libc_lock_trylock (NAME)

/* Unlock the named lock variable.  */
#define __libc_lock_unlock(NAME) pthread_mutex_unlock (&(NAME));
#define __libc_rwlock_unlock(NAME) pthread_rwlock_unlock (&(NAME));

/* Unlock the recursive named lock variable.  */
#define __libc_lock_unlock_recursive(NAME) __libc_lock_unlock (NAME)


/* Define once control variable.  */
#else
#define __libc_once_define(CLASS, NAME) \
  CLASS pthread_once_t NAME = PTHREAD_ONCE_INIT

/* Call handler iff the first call.  */
#define __libc_once(ONCE_CONTROL, INIT_FUNCTION) \
  pthread_once (&(ONCE_CONTROL), (INIT_FUNCTION));

/* Start critical region with cleanup.  */
#define __libc_cleanup_region_start(FCT, ARG) \
  pthread_cleanup_push_defer_np ((FCT), (ARG));

/* End critical region with cleanup.  */
#define __libc_cleanup_region_end(DOIT) pthread_cleanup_pop_restore_np ((DOIT));

/* Sometimes we have to exit the block in the middle.  */
#define __libc_cleanup_end(DOIT) pthread_cleanup_pop_restore_np ((DOIT));

/* Create thread-specific key.  */
#define __libc_key_create(KEY, DESTRUCTOR) pthread_key_create (KEY, DESTRUCTOR)

/* Get thread-specific data.  */
#define __libc_getspecific(KEY) pthread_getspecific (KEY)

/* Set thread-specific data.  */
#define __libc_setspecific(KEY, VALUE) pthread_setspecific (KEY, VALUE)


/* Register handlers to execute before and after `fork'.  */
#define __libc_atfork(PREPARE, PARENT, CHILD) pthread_atfork (PREPARE, PARENT, CHILD)

/* We need portable names for some functions.  E.g., when they are
   used as argument to __libc_cleanup_region_start.  */
#define __libc_mutex_unlock pthread_mutex_unlock

#endif	/* bits/libc-lock.h */
