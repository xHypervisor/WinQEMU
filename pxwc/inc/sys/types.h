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

#ifndef _SYS_TYPES_
#define _SYS_TYPES_

#pragma pack (push, 8)

#include <features.h>

#ifdef	__USE_BSD
# if !defined __bsd_t_defined && !defined _WINSOCK_H && \
     !defined _WINSOCKAPI_ && !defined _WINSOCK2API_
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef __int64 quad_t;
typedef unsigned __int64 u_quad_t;
typedef u_quad_t fsid_t;
#  define __bsd_t_defined
# endif
# if !defined __bsd_t_defined
typedef __int64 quad_t;
typedef unsigned __int64 u_quad_t;
typedef u_quad_t fsid_t;
#  define __bsd_t_defined
# endif
#endif

#define	__need_size_t
#include <stddef.h>

typedef __int64 loff_t;

#ifndef __ino_t_defined
# ifndef __USE_FILE_OFFSET64
#ifndef _MSC_VER
typedef unsigned long ino_t;
#endif
# else
typedef unsigned __int64 ino_t;
# endif
# define __ino_t_defined
#endif
#if defined __USE_LARGEFILE64 && !defined __ino64_t_defined
typedef unsigned __int64 ino64_t;
# define __ino64_t_defined
#endif

#ifndef __dev_t_defined
#ifndef _MSC_VER
typedef short dev_t;
#endif
# define __dev_t_defined
#endif

#ifndef __gid_t_defined
typedef unsigned long gid_t;
# define __gid_t_defined
#endif

#ifndef __mode_t_defined
typedef unsigned long mode_t;
# define __mode_t_defined
#endif

#ifndef __nlink_t_defined
typedef unsigned short nlink_t;
# define __nlink_t_defined
#endif

#ifndef __uid_t_defined
typedef unsigned long uid_t;
# define __uid_t_defined
#endif

#ifndef __off_t_defined
# ifndef __USE_FILE_OFFSET64
typedef long off_t;
# else
typedef __int64 off_t;
# endif
# define __off_t_defined
#endif
#if defined __USE_LARGEFILE64 && !defined __off64_t_defined
typedef __int64 off64_t;
# define __off64_t_defined
#endif

#ifndef __pid_t_defined
typedef long int pid_t;
# define __pid_t_defined
#endif

#if (defined __USE_SVID || defined __USE_XOPEN) && !defined __id_t_defined
typedef unsigned int id_t;
# define __id_t_defined
#endif

#ifndef __ssize_t_defined
typedef size_t ssize_t;
# define __ssize_t_defined
#endif

#ifdef	__USE_BSD
# ifndef __daddr_t_defined
typedef size_t daddr_t;
typedef char *caddr_t;
#  define __daddr_t_defined
# endif
#endif

#if (defined __USE_SVID || defined __USE_XOPEN) && !defined __key_t_defined
typedef long key_t;
# define __key_t_defined
#endif

#ifdef __USE_XOPEN
# define __need_clock_t
#endif
#define	__need_time_t
/* Timer ID returned by `timer_create'.  */
#define __need_timer_t
/* Clock ID used in clock and timer functions.  */
#define __need_clockid_t
#include <time.h>

#ifdef __USE_XOPEN
# ifndef __useconds_t_defined
typedef unsigned int useconds_t;
#  define __useconds_t_defined
# endif
# ifndef __suseconds_t_defined
typedef long suseconds_t;
#  define __suseconds_t_defined
# endif
#endif

#ifdef __USE_MISC
/* Old compatibility names for C types.  */
typedef unsigned long ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
#endif


/* These size-specific names are used by some of the inet code.  */

#ifdef __GNUC__
# if !__GNUC_PREREQ (2, 7)

#  ifndef __int8_t_defined
/* These types are defined by the ISO C99 header <inttypes.h>. */
#   define __int8_t_defined
typedef	char int8_t;
typedef	short int int16_t;
typedef	int int32_t;
typedef long long int64_t;
#  endif

/* But these were defined by ISO C without the first `_'.  */
typedef	unsigned char u_int8_t;
typedef	unsigned short int u_int16_t;
typedef	unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

typedef int register_t;

# else
/* For GCC 2.7 and later, we can use specific type-size attributes.  */
#  define __intN_t(N, MODE) \
  typedef int int##N##_t __attribute__ ((__mode__ (MODE)))
#  define __u_intN_t(N, MODE) \
  typedef unsigned int u_int##N##_t __attribute__ ((__mode__ (MODE)))

#  ifndef __int8_t_defined
#   define __int8_t_defined
__intN_t (8, __QI__);
__intN_t (16, __HI__);
__intN_t (32, __SI__);
__intN_t (64, __DI__);
#  endif

__u_intN_t (8, __QI__);
__u_intN_t (16, __HI__);
__u_intN_t (32, __SI__);
__u_intN_t (64, __DI__);

typedef int register_t __attribute__ ((__mode__ (__word__)));

# endif
#else

# ifndef __int8_t_defined
/* These types are defined by the ISO C99 header <inttypes.h>. */
#  define __int8_t_defined
typedef	__int8 int8_t;
typedef	__int16 int16_t;
typedef	__int32 int32_t;
typedef __int64 int64_t;
# endif

/* But these were defined by ISO C without the first `_'.  */
typedef	unsigned __int8 u_int8_t;
typedef	unsigned __int16 u_int16_t;
typedef	unsigned __int32 u_int32_t;
typedef unsigned __int64 u_int64_t;

typedef int register_t;

#endif
#define __BIT_TYPES_DEFINED__	1

#ifdef	__USE_BSD
/* In BSD <sys/types.h> is expected to define BYTE_ORDER.  */
# include <endian.h>

/* It also defines `fd_set' and the FD_* macros for `select'.  */
# include <sys/select.h>

/* BSD defines these symbols, so we follow.  */
# include <sys/sysmacros.h>
#endif /* Use BSD.  */


#if defined __USE_UNIX98 && !defined __blksize_t_defined
typedef __int64 blksize_t;
# define __blksize_t_defined
#endif

/* Types from the Large File Support interface. */
#ifndef __USE_FILE_OFFSET64
# ifndef __blkcnt_t_defined
typedef long int blkcnt_t; /* Type to count number of disk blocks.  */
#  define __blkcnt_t_defined
# endif
# ifndef __fsblkcnt_t_defined
typedef unsigned long int fsblkcnt_t; /* Type to count file system blocks.  */
#  define __fsblkcnt_t_defined
# endif
# ifndef __fsfilcnt_t_defined
typedef unsigned long int fsfilcnt_t; /* Type to count file system inodes.  */
#  define __fsfilcnt_t_defined
# endif
#else
# ifndef __blkcnt_t_defined
typedef __int64 blkcnt_t; /* Type to count number of disk blocks.  */
#  define __blkcnt_t_defined
# endif
# ifndef __fsblkcnt_t_defined
typedef unsigned __int64 fsblkcnt_t; /* Type to count file system blocks. */
#  define __fsblkcnt_t_defined
# endif
# ifndef __fsfilcnt_t_defined
typedef unsigned __int64 fsfilcnt_t; /* Type to count file system inodes. */
#  define __fsfilcnt_t_defined
# endif
#endif

#ifdef __USE_LARGEFILE64
typedef __int64 blkcnt64_t; /* Type to count number of disk blocks. */
typedef unsigned __int64 fsblkcnt64_t; /* Type to count file system blocks.  */
typedef unsigned __int64 fsfilcnt64_t; /* Type to count file system inodes.  */
#endif

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

#endif /* sys/types.h */