#ifndef __MATH_EX_H__
#define __MATH_EX_H__

#include <math.h>

 #pragma comment(lib,"libmmds.lib") 

#ifdef __cplusplus
extern "C"
{
#endif

#define _LIBIMF_INT int
# define FP_NAN       (0)
# define FP_INFINITE  (1)
# define FP_ZERO      (2)
# define FP_SUBNORMAL (3)
# define FP_NORMAL    (4)

// From mathimf.h
_LIBIMF_INT isgreaterf( float xf, float yf );
_LIBIMF_INT isgreater( double xd, double yd );
_LIBIMF_INT isgreaterl( long double xl, long double yl );
_LIBIMF_INT __isgreaterf( float xf, float yf );
#define __isgreaterf __isgreater
_LIBIMF_INT __isgreater( double xd, double yd );
_LIBIMF_INT __isgreaterl( long double xl, long double yl );

_LIBIMF_INT isgreaterequalf( float xf, float yf );
_LIBIMF_INT isgreaterequal( double xd, double yd );
_LIBIMF_INT isgreaterequall( long double xl, long double yl );
_LIBIMF_INT __isgreaterequalf( float xf, float yf );
_LIBIMF_INT __isgreaterequal( double xd, double yd );
_LIBIMF_INT __isgreaterequall( long double xl, long double yl );

_LIBIMF_INT islessf( float xf, float yf );
_LIBIMF_INT isless( double xd, double yd );
_LIBIMF_INT islessl( long double xl, long double yl );
//_LIBIMF_INT __islessf( float xf, float yf );
#define __islessf __isless
_LIBIMF_INT __isless( double xd, double yd );
_LIBIMF_INT __islessl( long double xl, long double yl );

_LIBIMF_INT islessequalf( float xf, float yf );
_LIBIMF_INT islessequal( double xd, double yd );
_LIBIMF_INT islessequall( long double xl, long double yl );
_LIBIMF_INT __islessequalf( float xf, float yf );
_LIBIMF_INT __islessequal( double xd, double yd );
_LIBIMF_INT __islessequall( long double xl, long double yl );

_LIBIMF_INT islessgreaterf( float xf, float yf );
_LIBIMF_INT islessgreater( double xd, double yd );
_LIBIMF_INT islessgreaterl( long double xl, long double yl );
_LIBIMF_INT __islessgreaterf( float xf, float yf );
_LIBIMF_INT __islessgreater( double xd, double yd );
_LIBIMF_INT __islessgreaterl( long double xl, long double yl );

//_LIBIMF_INT isunorderedf( float xf, float yf );
#define isunorderedf isunordered
_LIBIMF_INT isunordered( double xd, double yd );
_LIBIMF_INT isunorderedl( long double xl, long double yl );
//_LIBIMF_INT __isunorderedf( float xf, float yf );
#define __isunorderedf __isunordered
_LIBIMF_INT __isunordered( double xd, double yd );
_LIBIMF_INT __isunorderedl( long double xl, long double yl );



#define _LIBIMF_LONGINT long
#define _LIBIMF_LONGLONG long long
#define _LIBIMF_DOUBLE double
#define _LIBIMF_FLOAT float

_LIBIMF_LONGINT   lrint( _LIBIMF_DOUBLE __x );
_LIBIMF_LONGINT   lrintf( _LIBIMF_FLOAT __x );

_LIBIMF_LONGLONG  llrint( _LIBIMF_DOUBLE __x );
_LIBIMF_LONGLONG  llrintf( _LIBIMF_FLOAT __x );
_LIBIMF_DOUBLE   rint( _LIBIMF_DOUBLE __x );
_LIBIMF_FLOAT    rintf( _LIBIMF_FLOAT __x );
//# define lrintl       lrint
//# define llrintl      llrint
//# define rintl        rint

_LIBIMF_DOUBLE    round( _LIBIMF_DOUBLE __x );
_LIBIMF_FLOAT     roundf( _LIBIMF_FLOAT __x );

_LIBIMF_LONGINT   lround( _LIBIMF_DOUBLE __x );
_LIBIMF_LONGINT   lroundf( _LIBIMF_FLOAT __x );

_LIBIMF_LONGLONG  llround( _LIBIMF_DOUBLE __x );
_LIBIMF_LONGLONG  llroundf( _LIBIMF_FLOAT __x );

_LIBIMF_DOUBLE    trunc( _LIBIMF_DOUBLE __x );
_LIBIMF_FLOAT     truncf( _LIBIMF_FLOAT __x );

_LIBIMF_DOUBLE   remainder( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_FLOAT    remainderf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
# define remainderl   remainder

int fesetround (int round) ;

__inline int ffs(int x)
{
	int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}

#ifdef __cplusplus
}
#endif

//#if (defined(__i386__) || defined(__x86_64__)) && !defined(_BSD)
//#define FLOATX80 // TODO
//#endif
//
//typedef float float32;
//typedef double float64;
//
//#ifdef FLOATX80
//
//#if defined (__USE_MSVC) && defined(__USE_FLOAT80_EXT)
//#include "float80-port.h"
//#else
//typedef long double floatx80;
//#endif
//
//#else
//typedef long double floatx80; // BUGBUG
//#endif
//
//float32 rintf (float32 Value);
//float64 rint (float64 Value);
//
//int32_t lrintf (float32 Value);
//int32_t lrint (float64 Value);
//
//
//int64_t llrintf (float32 Value);
//int64_t llrint (float64 Value);
//
//
//float32 remainderf (float32, float32);
//float64 remainder (float64, float64);
//
//
//
//int fesetround (int mode);
//
//bool isunordered (float32 l, float32 r);
//bool isunordered (float64 &l, float64 &r);
//bool isunordered (long double &l, long double &r);
//
//int32_t lrintl (floatx80 Value);
//floatx80 rintl (floatx80 Value);
//int64_t llrintl (floatx80 Value);
//bool isunordered (floatx80 &l, floatx80 &r);
//floatx80 remainderl (floatx80, floatx80);
//
//template <typename T>
//inline bool isless (T l, T r)
//{
//	return ((!isunordered (l, r)) && (l < r));
//}
//
//template <typename T>
//inline bool isgreater (T l, T r)
//{
//	return ((!isunordered (l, r)) && (l > r));
//}
//
//template <typename T>
//inline bool islessequal (T l, T r)
//{
//	return ((!isunordered (l, r)) && (l <= r));
//}
//
////#define lrint(d)		((int32_t)rint(d))
////#define lrintf(f)		((int32_t)rintf(f))
////#define lrintl(l)		((int32_t)rintl(l))
////
////#define llrint(d)		((int64_t)rint(d))
////#define llrintf(f)		((int64_t)rintf(f))
////#define llrintl(l)		((int64_t)rintl(l))
_LIBIMF_INT fpclassify( _LIBIMF_DOUBLE __x );
_LIBIMF_FLOAT  scalbnf( _LIBIMF_FLOAT __x, _LIBIMF_INT __n );

#endif //
