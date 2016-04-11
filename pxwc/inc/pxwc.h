 /**************************************************************************\
 *                                                                          *
 *   pxwc - wgcc's gcc to cl libc wrapper                                   *
 *   Copyright (C) 2006  Markus Duft <markus.duft@salomon.at>               *
 *                                                                          *
 *   This library is free software; you can redistribute it and/or          *
 *   modify it under the terms of the GNU Lesser General Public             *
 *   License as published by the Free Software Foundation; either           *
 *   version 2.1 of the License, or (at your option) any later version.     *
 *                                                                          *
 *   This library is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *   Lesser General Public License for more details.                        *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with this library; if not, write to the Free Software    *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,             *
 *   MA  02110-1301 USA                                                     *
 *                                                                          *
 \**************************************************************************/

#ifndef _WIN32
#error This Header is intended for use on Windows only!
#endif

 /**************************************************************************\
 *                                                                          *
 * whatever you're about to do in here: be _extremely_ carefull, and don't  *
 * touch anything you don't understand 100% ;o). There is more than one     *
 * really bad hack in here that depends on about 100 (;o)) conditions.      *
 *                                                                          *
 \**************************************************************************/

#ifndef __PXWC_PXWC_H__
#define __PXWC_PXWC_H__

#define __PXWC__ 		2	
#define __PXWC_MINOR__ 	0
#define __PXWC_MICRO__	2

#ifndef __CRTDLL
	#ifdef _DLL
		#define __CRTDLL __declspec(dllimport)
	#else
		#define __CRTDLL
	#endif
#endif

#ifdef __cplusplus
#define PXWC_INLINE inline
#else
#define PXWC_INLINE
#endif

#define __CLEANUP_C			/* pthread C cleanup code */
#define _WIN32_WINNT 0x0500 /* Windows 2000 min System req, NT would do, but may conflict with other progs */

typedef signed int ssize_t;

/* Define getenv to use the pxwc internal getenv in win_paths.c */
#define getenv __pxwc_getenv

#include "alloca.h"			/* Everybody want's it, but few include it... */
#include "readlink.h"		/* Needed by libiconv		*/
#include <sys/stat.h>		/* Include before redefine */
#include <sys/timeb.h>		/* Include before redefine */
#include <sys/types.h>		/* LM2 (Tools) needs it */
#include <io.h>
#include <limits.h>

#ifdef __cplusplus
	extern "C" {
#endif

/* stuff to enable memory debugging facilities from pxwc */
#if defined(PXWC_MEMORY_PROFILER)
	
	#ifndef _DEBUG
		#define _DEBUG 1
	#endif

	/* static dummy to allways reference __crt_memory */
	extern int __pxwc_set_memory_debug_class_reference_dummy();
	static int (*__pxwc_set_memory_debug_class_reference_dummy_referencer)() = __pxwc_set_memory_debug_class_reference_dummy;

	/* need some headers _before_ debug includes */
	#include <stdlib.h>
	#include <malloc.h>
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

	/* prototypes for controlling functions: */
	static void __pxwc_memory_dump() { __internal_pxwc_memory_dump(); }
	static void __pxwc_memory_dump_positional() { __internal_pxwc_memory_dump_positional(); }
	static void __pxwc_memory_leak() { __internal_pxwc_memory_leak(); }

	static int __debug_crt_indicator__ = 0;
#else /* PXWC_MEMORY_PROFILER */
	static void __pxwc_memory_dump() {}
	static void __pxwc_memory_dump_positional() {}
	static void __pxwc_memory_leak() {}
#endif /* PXWC_MEMORY_PROFILER */

/* This is future ;o)
static void* (*__pxwc_malloc)	(size_t size)				= malloc;
static void  (*__pxwc_free)		(void* block)				= free;
static void* (*__pxwc_realloc)	(void* block, size_t size)	= realloc;
static void* (*__pxwc_calloc)	(size_t num, size_t size)	= calloc;
*/

/* microsoft does it this way, so why not we too ;o) */
#ifdef _DLL
	extern __CRTDLL char *** __cdecl __p__environ(void);
	#define _environ (*__p__environ())
#else /* _DLL */
	extern char ** _environ;
#endif /* _DLL */

/* allways define the following functions: */
extern __CRTDLL int __cdecl _stricmp(const char*, const char*);
extern __CRTDLL int __cdecl _strnicmp(const char*, const char*, size_t len);
extern __CRTDLL int __cdecl _getpid();
extern __CRTDLL void __cdecl _sleep(unsigned long);
extern __CRTDLL __declspec(noreturn) void   __cdecl abort(void);
extern __CRTDLL __declspec(noreturn) void   __cdecl exit(int);

static PXWC_INLINE int strcasecmp(const char*a, const char*b)				{ return _stricmp(a, b); }
static PXWC_INLINE int strncasecmp(const char*a, const char*b, size_t c)	{ return _strnicmp(a, b, c); }
static PXWC_INLINE void sleep(unsigned long a)								{ _sleep(a); }

#ifdef __cplusplus
	} /* extern "C" {} */
#endif

#define snprintf		_snprintf
#define vsnprintf		_vsnprintf
#define popen			_popen
#define pclose			_pclose
#define getpid			_getpid
#define getcwd			_getcwd

#if defined(__STDC__)

	#ifdef __cplusplus
		extern "C" {
	#endif

	#define environ _environ

	#define timeb	_timeb
	#define stat	_stat
	typedef _off_t	off_t;

	struct _iobuf;

	extern __CRTDLL int __cdecl _access(const char*, int);
	extern __CRTDLL int __cdecl _write(int, const void*, unsigned int);
	extern __CRTDLL int __cdecl _open(const char*, int, ...);
	extern __CRTDLL int __cdecl _close(int);
	extern __CRTDLL int __cdecl _read(int,void*,unsigned int);
	extern __CRTDLL char * __cdecl _strdup(const char *);
	extern __CRTDLL int __cdecl _setmode(int, int);
	extern __CRTDLL int __cdecl _fileno(struct _iobuf *);
	extern __CRTDLL int __cdecl _fstat(int, struct _stat *);
	extern __CRTDLL int __cdecl _unlink(const char *);
	extern __CRTDLL void __cdecl _ftime(struct _timeb *);
	extern __CRTDLL int __cdecl _locking(int, int, long);
	extern __CRTDLL int __cdecl _stat(const char*, struct _stat*);

	static PXWC_INLINE int access(const char*path, int mode)				{ return _access(path, mode); }
	static PXWC_INLINE int write(int i, const void* v, unsigned int n)		{ return _write(i, v, n); }
	static PXWC_INLINE int open(const char* f, int i, int y)				{ return _open(f, i, y); }
	static PXWC_INLINE int close(int a)										{ return _close(a); }
	static PXWC_INLINE int read(int a, void* b, unsigned int c)				{ return _read(a, b, c); }
	static PXWC_INLINE char * strdup(const char * a)						{ return _strdup(a); }
	static PXWC_INLINE int setmode(int a, int b)							{ return _setmode(a, b); }
	static PXWC_INLINE int fileno(struct _iobuf *a)							{ return _fileno(a); }
	static PXWC_INLINE int fstat(int a, struct _stat * b)					{ return _fstat(a, b); }
	static PXWC_INLINE int lstat(const char*a, struct _stat*b)				{ return _stat(a, b); }
	static PXWC_INLINE int unlink(const char *a)							{ return _unlink(a); }
	static PXWC_INLINE int ftime(struct _timeb *a)							{ ftime(a); }
	static PXWC_INLINE int locking(int a, int b, long c)					{ return _locking(a, b, c); }

	#ifdef __cplusplus
		} /* extern "C" */
	#endif

	#define spawnlp			_spawnlp
	#define spawnl			_spawnl
	#define spawnlpe		_spawnlpe
	#define spawnv			_spawnv
	#define spawnve			_spawnve
	#define spawnvp			_spawnvp
	#define spawnvpe		_spawnvpe

	#define P_WAIT          _P_WAIT
	#define P_NOWAIT        _P_NOWAIT
	#define P_OVERLAY       _P_OVERLAY
	#define OLD_P_OVERLAY   _OLD_P_OVERLAY
	#define P_NOWAITO       _P_NOWAITO
	#define P_DETACH        _P_DETACH
	#define WAIT_CHILD      _WAIT_CHILD
	#define WAIT_GRANDCHILD _WAIT_GRANDCHILD

	#define TCHAR			_TCHAR

	#define LK_UNLCK		_LK_UNLCK
	#define LK_LOCK			_LK_LOCK
	#define LK_NBLCK		_LK_NBLCK
	#define LK_RLCK			_LK_RLCK
	#define LK_NBRLCK		_LK_NBRLCK

	#define S_IFMT			_S_IFMT
	#define S_IFDIR			_S_IFDIR
	#define S_IFCHR			_S_IFCHR
	#define S_IFREG			_S_IFREG
	#define S_IREAD			_S_IREAD
	#define S_IWRITE		_S_IWRITE
	#define S_IEXEC			_S_IEXEC

	#define O_RDONLY		_O_RDONLY
	#define O_WRONLY		_O_WRONLY
	#define O_RDWR			_O_RDWR
	#define O_APPEND		_O_APPEND
	#define O_CREAT			_O_CREAT
	#define O_TRUNC			_O_TRUNC
	#define O_EXCL			_O_EXCL
	#define O_TEXT			_O_TEXT
	#define O_BINARY		_O_BINARY
	#define O_RAW			_O_BINARY
	#define O_TEMPORARY		_O_TEMPORARY
	#define O_NOINHERIT		_O_NOINHERIT
	#define O_SEQUENTIAL	_O_SEQUENTIAL
	#define O_RANDOM		_O_RANDOM

#endif /* __STDC__ */

#define S_ISDIR(m) ( ((m) & S_IFMT) == S_IFDIR )
#define S_ISREG(m) ( ((m) & S_IFMT) == S_IFREG )
#define S_ISCHR(m) ( ((m) & S_IFMT) == S_IFCHR )

#ifndef _POSIX_
/*	Shamelessly taken from MS limits.h */
/*	It is included here, because MS Header requires
	_POSIX_ which i don't want to be defined... */

	#undef ARG_MAX
	#undef LINK_MAX
	#undef MAX_CANON
	#undef MAX_INPUT
	#undef NAME_MAX
	#undef NGROUPS_MAX
	#undef OPEN_MAX
	#undef PATH_MAX
	#undef PIPE_BUF
	#undef SSIZE_MAX
	#undef STREAM_MAX
	#undef TZNAME_MAX

	#define ARG_MAX             14500       /* 16k heap, minus overhead */
	#define LINK_MAX            1024
	#define MAX_CANON           255
	#define MAX_INPUT           255
	#define NAME_MAX            255
	#define NGROUPS_MAX         16
	#define OPEN_MAX            32
	#define PATH_MAX            512
	#define PIPE_BUF            512
	#define SSIZE_MAX           32767
	#define STREAM_MAX          20
	#define TZNAME_MAX          10

#endif

/* Improvements for sys/stat.h */
#define _S_PROT     00000777
#define S_IRWXU     00000700
#define S_IRUSR     00000400
#define S_IWUSR     00000200
#define S_IXUSR     00000100

#define S_IRWXG     00000700
#define S_IRGRP     00000400
#define S_IWGRP     00000200
#define S_IXGRP     00000100

#define S_IRWXO     00000700
#define S_IROTH     00000400
#define S_IWOTH     00000200
#define S_IXOTH     00000100

/* File Access Rights */
#define  F_OK  00
#define  X_OK  00
#define  W_OK  02
#define  R_OK  04

#endif
