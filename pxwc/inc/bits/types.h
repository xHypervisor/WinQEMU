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

#ifndef _BITS_TYPES_
#define _BITS_TYPES_

#pragma pack (push, 8)

#include <features.h>

#define __need_size_t
#include <stddef.h>

typedef unsigned char __u_char;
typedef unsigned short __u_short;
typedef unsigned int __u_int;
typedef unsigned long __u_long;
typedef __int64 __quad_t;
typedef unsigned __int64 __u_quad_t;
typedef __u_quad_t __fsid_t;

#define	__need_size_t
#include <stddef.h>

typedef __int64 __loff_t;

#ifndef __USE_FILE_OFFSET64
typedef unsigned long __ino_t;
#else
typedef unsigned __int64 __ino_t;
#endif
#if defined __USE_LARGEFILE64
typedef unsigned __int64 __ino64_t;
#endif

typedef short __dev_t;

typedef unsigned long __gid_t;

typedef unsigned long __mode_t;

typedef unsigned short __nlink_t;

typedef unsigned long __uid_t;

#ifndef __USE_FILE_OFFSET64
typedef long __off_t;
#else
typedef __int64 __off_t;
#endif
#if defined __USE_LARGEFILE64
typedef __int64 __off64_t;
#endif

typedef long int __pid_t; /* but may be unsigned short */

typedef unsigned int __id_t;

typedef size_t __ssize_t;

typedef size_t __daddr_t;
typedef char *__caddr_t;

typedef long __key_t;

typedef __u_long __rlim_t;      /* Type of resource counts.  */
typedef __u_quad_t __rlim64_t;  /* Type of resource counts (LFS).  */

#define __need_clock_t
#define	__need_time_t
/* Timer ID returned by `timer_create'.  */
#define __need_timer_t
/* Clock ID used in clock and timer functions.  */
#define __need_clockid_t
#include <time.h>

typedef unsigned int __useconds_t;
typedef long __suseconds_t;


/* These size-specific names are used by some of the inet code.  */

#ifdef __GNUC__
# if !__GNUC_PREREQ (2, 7)

typedef	char __int8_t;
typedef	short int __int16_t;
typedef	int __int32_t;
typedef long long __int64_t;

/* But these were defined by ISO C without the first `_'.  */
typedef	unsigned char __u_int8_t, __uint8_t;
typedef	unsigned short int __u_int16_t, __uint16_t;
typedef	unsigned int __u_int32_t, __uint32_t;
typedef unsigned long long __u_int64_t, __uint64_t;

# else
/* For GCC 2.7 and later, we can use specific type-size attributes.  */
#  define __intN_t(N, MODE) \
  typedef int __int##N##_t __attribute__ ((__mode__ (MODE)))
#  define __u_intN_t(N, MODE) typedef unsigned int __u_int##N##_t __attribute__ ((__mode__ (MODE)))

#  define __uintN_t(N, MODE) typedef unsigned int __u_int##N##_t __attribute__ ((__mode__ (MODE)))

__intN_t (8, __QI__);
__intN_t (16, __HI__);
__intN_t (32, __SI__);
__intN_t (64, __DI__);

__u_intN_t (8, __QI__);
__u_intN_t (16, __HI__);
__u_intN_t (32, __SI__);
__u_intN_t (64, __DI__);

__uintN_t (8, __QI__);
__uintN_t (16, __HI__);
__uintN_t (32, __SI__);
__uintN_t (64, __DI__);

# endif
#else

typedef	__int8 __int8_t;
typedef	__int16 __int16_t;
typedef	__int32 __int32_t;
typedef __int64 __int64_t;

/* But these were defined by ISO C without the first `_'.  */
typedef	unsigned __int8 __u_int8_t, __uint8_t;
typedef	unsigned __int16 __u_int16_t, __uint16_t;
typedef	unsigned __int32 __u_int32_t, __uint32_t;
typedef unsigned __int64 __u_int64_t, __uint64_t;

#endif


/* Number of descriptors that can fit in an `fd_set'.  */
#define __FD_SETSIZE	1024

typedef __int64 __blksize_t;

/* Types from the Large File Support interface. */
#ifndef __USE_FILE_OFFSET64
typedef long int __blkcnt_t; /* Type to count number of disk blocks.  */
typedef unsigned long int __fsblkcnt_t; /* Type to count file system blocks.  */
typedef unsigned long int __fsfilcnt_t; /* Type to count file system inodes.  */
#else
typedef __int64 __blkcnt_t; /* Type to count number of disk blocks.  */
typedef unsigned __int64 __fsblkcnt_t; /* Type to count file system blocks. */
typedef unsigned __int64 __fsfilcnt_t; /* Type to count file system inodes. */
#endif

#ifdef __USE_LARGEFILE64
typedef __int64 __blkcnt64_t; /* Type to count number of disk blocks. */
typedef unsigned __int64 __fsblkcnt64_t; /* Type to count file system blocks.  */
typedef unsigned __int64 __fsfilcnt64_t; /* Type to count file system inodes.  */
#endif

typedef void *__ptr_t;

#if defined __USE_POSIX199506 || defined __USE_UNIX98
# include <bits/pthreadtypes.h>

# ifndef __pthread_t_defined
typedef unsigned long pthread_t;
#  define __pthread_t_defined
# endif
# ifndef __pthread_attr_t_defined
typedef struct _THREAD_ATTRIBUTES pthread_attr_t;
#  define __pthread_attr_t_defined
# endif

# ifndef __pthread_mutex_t_defined
typedef struct _MUTANT pthread_mutex_t;
#  define __pthread_mutex_t_defined
# endif
# ifndef __pthread_mutexattr_t_defined
typedef struct _MUTANT_ATTRIBUTES pthread_mutexattr_t;
#  define __pthread_mutexattr_t_defined
# endif

# ifndef __pthread_cond_t_defined
typedef struct _CONDITION pthread_cond_t;
#  define __pthread_cond_t_defined
# endif
# ifndef __pthread_condattr_t_defined
typedef struct _CONDITION_ATTRIBUTES pthread_condattr_t;
#  define __pthread_condattr_t_defined
# endif

# ifndef __pthread_key_t_defined
typedef unsigned short int pthread_key_t;
#  define __pthread_key_t_defined
# endif

# ifndef __pthread_once_t_defined
typedef struct _ONCE_CONTROL pthread_once_t;
#  define __pthread_once_t_defined
# endif

# ifdef __USE_UNIX98
#  ifndef __pthread_rwlock_t_defined
typedef struct _RWLOCK pthread_rwlock_t;
#   define __pthread_rwlock_t_defined
#  endif
#  ifndef __pthread_rwlockattr_t_defined
typedef struct _RWLOCK_ATTRIBUTES pthread_rwlockattr_t;
#   define __pthread_rwlockattr_t_defined
#  endif
# endif

# ifdef __USE_XOPEN2K
#  ifndef __pthread_spinlock_t_defined
typedef struct _SPIN pthread_spinlock_t;
#   define __pthread_spinlock_t_defined
#  endif

#  ifndef __pthread_barrier_t_defined
typedef struct _BARRIER pthread_barrier_t;
#   define __pthread_barrier_t_defined
#  endif
#  ifndef __pthread_barrierattr_t_defined
typedef struct _BARRIER_ATTRIBUTES pthread_barrierattr_t;
#   define __pthread_barrierattr_t_defined
#  endif
# endif

#endif

#pragma pack (pop)

#endif /* bits/types.h */