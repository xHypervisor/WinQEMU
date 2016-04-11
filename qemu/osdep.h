/*
 * WinQEMU GPL Disclaimer: For the avoidance of doubt, except that if any license choice
 * other than GPL is available it will apply instead, WinQEMU elects to use only the 
 * General Public License version 3 (GPLv3) at this time for any software where a choice of 
 * GPL license versions is made available with the language indicating that GPLv3 or any later
 * version may be used, or where a choice of which version of the GPL is applied is otherwise unspecified.
 * 
 * Please contact Yan Wen (celestialwy@gmail.com) if you need additional information or have any questions.
 */
 
#ifndef QEMU_OSDEP_H
#define QEMU_OSDEP_H

#include <stdarg.h>
#ifdef __OpenBSD__
#include <sys/types.h>
#include <sys/signal.h>
#endif

#ifndef _WIN32
#include <sys/time.h>
#endif

#ifndef glue
#define xglue(x, y) x ## y
#define glue(x, y) xglue(x, y)
#define stringify(s)	tostring(s)
#define tostring(s)	#s
#endif

#ifndef likely
#if __GNUC__ < 3
#define __builtin_expect(x, n) (x)
#endif

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x)   __builtin_expect(!!(x), 0)
#endif

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *) 0)->MEMBER)
#endif
#ifndef container_of

#ifndef _MSC_VER
#define container_of(ptr, type, member) ({                      \
        const typeof(((type *) 0)->member) *__mptr = (ptr);     \
        (type *) ((char *) __mptr - offsetof(type, member));})
#else
#define container_of(ptr, type, member) ((type *) ((char *) ptr - offsetof(type, member)))
#endif

#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#ifndef always_inline
#if (__GNUC__ < 3) || defined(__APPLE__)
#define always_inline inline
#else
#define always_inline __attribute__ (( always_inline )) __inline__
#ifdef __OPTIMIZE__
#define inline always_inline
#endif
#endif
#else
#define inline always_inline
#endif

#ifdef __i386__

#ifdef _MSC_VER
#define REGPARM //__fastcall
#else
#define REGPARM __attribute((regparm(3)))
#endif

#else
#define REGPARM
#endif

#define qemu_printf printf

#if defined (__GNUC__) && defined (__GNUC_MINOR__)
# define QEMU_GNUC_PREREQ(maj, min) \
         ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define QEMU_GNUC_PREREQ(maj, min) 0
#endif

void *qemu_memalign(size_t alignment, size_t size);
void *qemu_vmalloc(size_t size);
void qemu_vfree(void *ptr);

int qemu_create_pidfile(const char *filename);

#ifdef _WIN32
int ffs(int i);

typedef struct {
    long tv_sec;
    long tv_usec;
} qemu_timeval;
int qemu_gettimeofday(qemu_timeval *tp);
#else
typedef struct timeval qemu_timeval;
#define qemu_gettimeofday(tp) gettimeofday(tp, NULL);
#endif /* !_WIN32 */

#endif
