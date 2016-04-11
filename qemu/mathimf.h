/* file: mathimf.h */

/*
** Copyright  (C) 1985-2006 Intel Corporation. All rights reserved.
**
** The information and source code contained herein is the exclusive property
** of Intel Corporation and may not be disclosed, examined, or reproduced in
** whole or in part without explicit written authorization from the Company.
**
** static char cvs_id[] = "$Id: mathimf.h,v 1.21.2.3 2006/05/14 07:30:58 pensil Exp $";
*/

/*
 * mathimf.h - Intel math library definitions
 *
 * Usage notes:
 * 1. This header file is for use with only  the Intel compilers!
 * 2. The 'long double' prototypes require the -Qlong_double (icl/ecl)
 *    or the -longdouble (icc/ecc) compiler option.
 * 3. The 'complex' prototypes are for use only with "C" (not "C++").
 * 4. Under icl/ecl, the 'complex' prototypes require the -Qc99 compiler option.
 * 5. The C99 _Complex and GNU __complex__ types are fully compatible.
 *
 */

#ifndef __MATHIMF_H_INCLUDED
#define __MATHIMF_H_INCLUDED

/* Check usage correctness */

//#if !defined(__INTEL_COMPILER)
//# error "<mathimf.h> is for use with only the Intel compilers!"
//#endif

#if defined(_WIN32) || defined(_WIN64)
# if defined(_INC_MATH)
#  error "<mathimf.h> is incompatible with system <math.h>!"
# else
#  define _INC_MATH /* Prevent possible inclusion of MS <math.h> below */
#  define __MATH_H_INCLUDED /* Prevent possible inclusion of Intel <math.h> below */
#  define __COMPLEX_H_INCLUDED /* Prevent possible inclusion of Intel <complex.h> below */
# endif
#endif

#if defined(__unix__) || defined(__APPLE__)
# include <math.h> /* utilize sys math header */
# if !defined(__cplusplus)
#  include <complex.h>
# endif
# define __IMFCOMPLEXON
#endif

#if (defined(_WIN32) || defined(_WIN64)) && defined (__STDC_VERSION__) &&  (__STDC_VERSION__ >= 199901L)
# define __IMFCOMPLEXON
#endif

#if defined(__linux__) || defined(__APPLE__)
# if defined(fpclassify)
#  undef fpclassify
# endif
# if defined(finite)
#  undef finite
# endif
# if defined(isnan)
#  undef isnan
# endif
# if defined(isinf)
#  undef isinf
# endif
# if defined(isnormal)
#  undef isnormal
# endif
# if defined(isfinite)
#  undef isfinite
# endif
# if defined(signbit)
#  undef signbit
# endif
#endif /* __linux__ */

#if defined(__linux__) || defined(__APPLE__)
# if defined(isgreater)
#  undef isgreater
# endif
# if defined(isless)
#  undef isless
# endif
# if defined(isgreaterequal)
#  undef isgreaterequal
# endif
# if defined(islessequal)
#  undef islessequal
# endif
# if defined(islessgreater)
#  undef islessgreater
# endif
# if defined(isunordered)
#  undef isunordered
# endif
#endif /* __linux__ || __APPLE__ */

#if !defined(__linux__) && !defined(__APPLE__)
static unsigned int __huge_valf[] = {0x7f800000};
#define HUGE_VALF (*(double *) __huge_valf)
static unsigned int __huge_vall[] = {0, 0, 0x00007f80, 0};
#define HUGE_VALL (*(long double *) __huge_vall)
static unsigned int __huge_val[] = {0, 0x7ff00000};
#define HUGE_VAL (*(double *) __huge_val)
static unsigned int __qnan[] = {0x7fc00001};
#define NAN (*((float *)__qnan))
static unsigned int __infinity[] = {0x7f800000};
#define INFINITY (*(float *) __infinity)
#endif

#if defined(__LONG_DOUBLE_SIZE__)	/* Compiler-predefined macros. If defined, should be 128|80|64 */
# define __IMFLONGDOUBLE (__LONG_DOUBLE_SIZE__)
#else
# define __IMFLONGDOUBLE 64
#endif

#if defined(__cplusplus)    /* C linkage */
extern "C" {
#endif

#define _LIBIMF_EXT extern

#if defined(_DLL) && (defined(_WIN32) || defined(_WIN64))   /* Windows DLL */
# define _LIBIMF_PUBAPI __declspec(dllimport) __cdecl
# define _LIBIMF_PUBAPI_INL __cdecl
# define _LIBIMF_PUBVAR     __declspec(dllimport)
#elif defined(__unix__) || defined(__APPLE__)             /* Linux, QNX, MacOS */
# define _LIBIMF_PUBAPI /* do not change this line! */
# define _LIBIMF_PUBAPI_INL
# define _LIBIMF_PUBVAR
#else                                             /* Windows static */
# define _LIBIMF_PUBAPI     __cdecl
# define _LIBIMF_PUBAPI_INL __cdecl
# define _LIBIMF_PUBVAR
#endif

#define _LIBIMF_LONGLONG long long int
#define _LIBIMF_LONGINT  long int
#define _LIBIMF_INT      int
#define _LIBIMF_DOUBLE   double
#define _LIBIMF_FLOAT    float
#define _LIBIMF_XDOUBLE  long double
#define _LIBIMF_VOID     void
#define _LIBIMF_CCHAR    const char


/*-- Classification macros --*/

#if defined (__IWMMXT__) || defined(__PURE_INTEL_C99_HEADERS__) || defined(_WIN32) || defined(_WIN64)
#if defined(__APPLE__)
#define FP_NAN          (1)
#define FP_INFINITE     (2)
#define FP_ZERO         (3)
#define FP_NORMAL       (4)
#define FP_SUBNORMAL    (5)
#else
# define FP_NAN       (0)
# define FP_INFINITE  (1)
# define FP_ZERO      (2)
# define FP_SUBNORMAL (3)
# define FP_NORMAL    (4)
#endif
#endif

#if !defined FP_NAN
# define FP_NAN       (0)
#endif
#if !defined FP_INFINITE
# define FP_INFINITE  (1)
#endif
#if !defined FP_ZERO
# define FP_ZERO      (2)
#endif
#if !defined FP_SUBNORMAL
# define FP_SUBNORMAL (3)
#endif
#if !defined FP_NORMAL
# define FP_NORMAL    (4)
#endif

_LIBIMF_EXT _LIBIMF_INT fpclassifyf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT fpclassifyl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT isfinitef( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT isfinitel( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT signbit( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT signbitf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT signbitl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT isnormalf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT isnormall( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnormalf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __isnormall( _LIBIMF_XDOUBLE __x );

#if defined (__APPLE__)
_LIBIMF_EXT _LIBIMF_INT fpclassifyd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isfinited( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnormald( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnormald( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT fpclassify( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isfinite( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnormal( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnormal( _LIBIMF_XDOUBLE __x );
#else
_LIBIMF_EXT _LIBIMF_INT fpclassify( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isfinite( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnormal( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnormal( _LIBIMF_DOUBLE __x );
#endif

#if (!(defined(__linux__) && defined(__USE_ISOC99))) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_INT __fpclassifyf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __fpclassifyl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT __finite( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __finitef( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __finitel( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT finite( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT finitef( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT finitel( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT isinff( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT isinfl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isinff( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __isinfl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT isnanf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT isnanl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnanf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __isnanl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT __signbit( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __signbitf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_INT __signbitl( _LIBIMF_XDOUBLE __x );

#if defined (__APPLE__)
_LIBIMF_EXT _LIBIMF_INT __fpclassifyd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isinfd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isinfd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnand( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnand( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_INT __fpclassify( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isinf( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isinf( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnan( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnan( _LIBIMF_XDOUBLE __x );
#else
_LIBIMF_EXT _LIBIMF_INT __fpclassify( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isinf( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isinf( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT isnan( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT __isnan( _LIBIMF_DOUBLE __x );
#endif
#endif /* __USE_ISOC99 */

#if defined (__APPLE__)
#define __IMFC99MACRO1ARG( __x__, __func__ ) \
	(( sizeof( __x__ ) > sizeof( double )) \
	 ? __func__( (long double)(__x__) ) \
	 : (( sizeof( __x__ ) == sizeof( float )) \
	    ? __func__##f( (float)(__x__) ) \
		: __func__##d( (double)(__x__) )))
#else
#define __IMFC99MACRO1ARG( __x__, __func__ ) \
	(( sizeof( __x__ ) > sizeof( double )) \
	 ? __func__##l( (long double)(__x__) ) \
	 : (( sizeof( __x__ ) == sizeof( float )) \
	    ? __func__##f( (float)(__x__) ) \
		: __func__( (double)(__x__) )))
#endif

#define __IMFC99MACRO1ARG_l( __x__, __func__ ) \
	(( sizeof( __x__ ) > sizeof( double )) \
	 ? __func__##l( (long double)(__x__) ) \
	 : (( sizeof( __x__ ) == sizeof( float )) \
	    ? __func__##f( (float)(__x__) ) \
		: __func__( (double)(__x__) )))

#define fpclassify( __x__ ) __IMFC99MACRO1ARG( __x__, __fpclassify )
#define isinf( __x__ )      __IMFC99MACRO1ARG( __x__, __isinf )
#define isnan( __x__ )      __IMFC99MACRO1ARG( __x__, __isnan )
#define isnormal( __x__ )   __IMFC99MACRO1ARG( __x__, __isnormal )

#define isfinite( __x__ )   __IMFC99MACRO1ARG_l( __x__, __finite )
#define signbit( __x__ )    __IMFC99MACRO1ARG_l( __x__, __signbit )

/* Comparison macros */

_LIBIMF_EXT _LIBIMF_INT isgreaterf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT isgreater( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT isgreaterl( long double xl, long double yl );
_LIBIMF_EXT _LIBIMF_INT __isgreaterf( float xf, float yf );
#define __isgreaterf __isgreater
_LIBIMF_EXT _LIBIMF_INT __isgreater( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __isgreaterl( long double xl, long double yl );

_LIBIMF_EXT _LIBIMF_INT isgreaterequalf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT isgreaterequal( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT isgreaterequall( long double xl, long double yl );
_LIBIMF_EXT _LIBIMF_INT __isgreaterequalf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT __isgreaterequal( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __isgreaterequall( long double xl, long double yl );

_LIBIMF_EXT _LIBIMF_INT islessf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT isless( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT islessl( long double xl, long double yl );
//_LIBIMF_EXT _LIBIMF_INT __islessf( float xf, float yf );
#define __islessf __isless
_LIBIMF_EXT _LIBIMF_INT __isless( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __islessl( long double xl, long double yl );

_LIBIMF_EXT _LIBIMF_INT islessequalf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT islessequal( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT islessequall( long double xl, long double yl );
_LIBIMF_EXT _LIBIMF_INT __islessequalf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT __islessequal( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __islessequall( long double xl, long double yl );

_LIBIMF_EXT _LIBIMF_INT islessgreaterf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT islessgreater( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT islessgreaterl( long double xl, long double yl );
_LIBIMF_EXT _LIBIMF_INT __islessgreaterf( float xf, float yf );
_LIBIMF_EXT _LIBIMF_INT __islessgreater( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __islessgreaterl( long double xl, long double yl );

//_LIBIMF_EXT _LIBIMF_INT isunorderedf( float xf, float yf );
#define isunorderedf isunordered
_LIBIMF_EXT _LIBIMF_INT isunordered( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT isunorderedl( long double xl, long double yl );
//_LIBIMF_EXT _LIBIMF_INT __isunorderedf( float xf, float yf );
#define __isunorderedf __isunordered
_LIBIMF_EXT _LIBIMF_INT __isunordered( double xd, double yd );
_LIBIMF_EXT _LIBIMF_INT __isunorderedl( long double xl, long double yl );

#define __IMFC99MACRO2ARG( __x__, __y__, __func__ ) \
	((( sizeof( __x__ ) > sizeof( double )) || ( sizeof( __y__ ) > sizeof( double ))) \
	 ? __func__##l( (long double)(__x__), (long double)(__y__) ) \
	 : ((( sizeof( __x__ ) + sizeof( __y__ )) == (2*sizeof( float ))) \
		? __func__##f( (float)(__x__), (float)(__y__) ) \
		: __func__( (double)(__x__), (double)(__y__) )))

#define isgreater( __x__, __y__ )       __IMFC99MACRO2ARG( __x__, __y__, __isgreater )
#define isgreaterequal( __x__, __y__ )  __IMFC99MACRO2ARG( __x__, __y__, __isgreaterequal )
#define isless( __x__, __y__ )          __IMFC99MACRO2ARG( __x__, __y__, __isless )
#define islessequal( __x__, __y__ )     __IMFC99MACRO2ARG( __x__, __y__, __islessequal )
#define islessgreater( __x__, __y__ )   __IMFC99MACRO2ARG( __x__, __y__, __islessgreater )
#define isunordered( __x__, __y__ )     __IMFC99MACRO2ARG( __x__, __y__, __isunordered )

/*-- Real functions --*/

/* Radian argument trigonometric functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI acos( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI asin( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI atan( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI_INL atan2( _LIBIMF_DOUBLE __y, _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cos( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI sin( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI tan( _LIBIMF_DOUBLE __x );

#endif  /* __unix__ && !__APPLE__ */

#if !defined(__unix__) && !defined(__APPLE__) 
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI acosf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI asinf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI atanf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI_INL atan2f( _LIBIMF_FLOAT __y, _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cosf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI sinf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI tanf( _LIBIMF_FLOAT __x );
#endif

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cot( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cotf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cotl( _LIBIMF_XDOUBLE __x );

#if defined(__APPLE__) || !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincos( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE *__psin, _LIBIMF_DOUBLE *__pcos );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincosf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT *__psin, _LIBIMF_FLOAT *__pcos );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincosl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE *__psin, _LIBIMF_XDOUBLE *__pcos );
#endif /* __USE_ISOC99 */

/* Degree argument trigonometric functions */

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cosd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cosdf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cosdl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI sind( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI sindf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI sindl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI tand( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI tandf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI tandl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cotd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cotdf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cotdl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI acosd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI acosdf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI acosdl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI asind( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI asindf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI asindl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI atand( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI atandf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atandl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI atand2( _LIBIMF_DOUBLE __y, _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI atand2f( _LIBIMF_FLOAT __y, _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atand2l( _LIBIMF_XDOUBLE __y, _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI atan2d( _LIBIMF_DOUBLE __y, _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI atan2df( _LIBIMF_FLOAT __y, _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atan2dl( _LIBIMF_XDOUBLE __y, _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincosd( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE *__psin, _LIBIMF_DOUBLE *__pcos );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincosdf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT *__psin, _LIBIMF_FLOAT *__pcos );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sincosdl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE *__psin, _LIBIMF_XDOUBLE *__pcos );

/* Hyperbolic functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI acosh( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI acoshf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI asinh( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI asinhf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI atanh( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI atanhf( _LIBIMF_FLOAT __x );
#endif  /* !__unix__ && !__APPLE__ */

_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sinhcosh( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE *__psinh, _LIBIMF_DOUBLE *__pcosh );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sinhcoshf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT *__psinh, _LIBIMF_FLOAT *__pcosh );
_LIBIMF_EXT _LIBIMF_VOID     _LIBIMF_PUBAPI sinhcoshl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE *__psinh, _LIBIMF_XDOUBLE *__pcosh );

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cosh( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI sinh( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI tanh( _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined(__unix__) && !defined(__APPLE__)) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI coshf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI sinhf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI tanhf( _LIBIMF_FLOAT __x );
#endif

/* Exponential functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI exp( _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined(__unix__) && !defined(__APPLE__)) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI expf( _LIBIMF_FLOAT __x );
#endif

#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI expm1( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI expm1f( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI exp2( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI exp2f( _LIBIMF_FLOAT __x );

#endif /* __USE_ISOC99 */

#if !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI exp10( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI exp10f( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI exp10l( _LIBIMF_XDOUBLE __x );
#endif /* __USE_ISOC99 */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI frexp( _LIBIMF_DOUBLE __x, _LIBIMF_INT *__exp );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI ldexp( _LIBIMF_DOUBLE __x, _LIBIMF_INT __exp );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined(__unix__) && !defined(__APPLE__)) 
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI frexpf( _LIBIMF_FLOAT __x, _LIBIMF_INT *__exp );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI ldexpf( _LIBIMF_FLOAT __x, _LIBIMF_INT __exp );
#endif

#if !defined(__APPLE__) && (!defined(__unix__) || !defined (__USE_ISOC99) || (defined (__USE_ISOC99) && !defined (__USE_MISC) && !defined (__USE_XOPEN_EXTENDED)))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI scalb( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
#endif

#if !defined(__unix__) || !defined (__USE_ISOC99) || (defined (__USE_ISOC99) && !defined (__USE_MISC) && !defined (__USE_XOPEN_EXTENDED))
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI scalbf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI scalbl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
#endif

#if (!defined(__unix__) && !defined(__APPLE__))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI scalbn( _LIBIMF_DOUBLE __x, _LIBIMF_INT __n );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI scalbnf( _LIBIMF_FLOAT __x, _LIBIMF_INT __n );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99)))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI scalbln( _LIBIMF_DOUBLE __x, _LIBIMF_LONGINT __n );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI scalblnf( _LIBIMF_FLOAT __x, _LIBIMF_LONGINT __n );
#endif /* __USE_ISOC99 */

/* Logarithmic functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI log( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI log10( _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI logf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI log10f( _LIBIMF_FLOAT __x );
#endif

#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI log2( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI log2f( _LIBIMF_FLOAT __x );
#endif /* __USE_ISOC99 */

#if (!defined(__unix__) && !defined(__APPLE__))

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI log1p( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI log1pf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI logb( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI logbf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_INT      _LIBIMF_PUBAPI ilogb( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT      _LIBIMF_PUBAPI ilogbf( _LIBIMF_FLOAT __x );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI modf( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE *__iptr );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI modff( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT *__iptr );
#endif

/* Power/root/abs functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cbrt( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cbrtf( _LIBIMF_FLOAT __x );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI_INL fabs( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI pow( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI_INL sqrt( _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI_INL fabsf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI hypot( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI hypotf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI powf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI_INL sqrtf( _LIBIMF_FLOAT __x );
#endif

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI invsqrt( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI invsqrtf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI invsqrtl( _LIBIMF_XDOUBLE __x );

/* Error and gamma functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI erf( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI erff( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI erfc( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI erfcf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI lgamma( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI lgammaf( _LIBIMF_FLOAT __x );

#endif  /*!__unix__ && !__APPLE__*/

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI gamma_r( _LIBIMF_DOUBLE __x, _LIBIMF_INT *__signgam );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI gammaf_r( _LIBIMF_FLOAT __x, _LIBIMF_INT *__signgam );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI gammal_r( _LIBIMF_XDOUBLE __x, _LIBIMF_INT *__signgam );

#if !defined(__unix__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI gamma( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI gammal( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI gammaf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI lgammaf_r( _LIBIMF_FLOAT __x, _LIBIMF_INT *__signgam );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI lgamma_r( _LIBIMF_DOUBLE __x, _LIBIMF_INT *__signgam );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI lgammal_r( _LIBIMF_XDOUBLE __x, _LIBIMF_INT *__signgam );
#endif  /* !__unix__ */


#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI tgamma( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI tgammaf( _LIBIMF_FLOAT __x );
#endif /* __USE_ISOC99 */

/* Nearest integer functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI ceil( _LIBIMF_DOUBLE __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI floor( _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/


#if (!defined(__unix__) && !defined(__APPLE__)) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI ceilf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI floorf( _LIBIMF_FLOAT __x );
#endif

#if (!defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI nearbyint( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI nearbyintf( _LIBIMF_FLOAT __x );
#endif /* __USE_ISOC99 */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI rint( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI rintf( _LIBIMF_FLOAT __x );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))) || defined(__PURE_INTEL_C99_HEADERS__)
_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lrint( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lrintf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llrint( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llrintf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI round( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI roundf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lround( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lroundf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llround( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llroundf( _LIBIMF_FLOAT __x );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI trunc( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI truncf( _LIBIMF_FLOAT __x );
#endif /* __USE_ISOC99 */

/* Remainder functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI fmod( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined(__unix__) && !defined(__APPLE__) 
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI fmodf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
#endif

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI remainder( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI remainderf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI remquo( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y, _LIBIMF_INT *__quo );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI remquof( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y, _LIBIMF_INT *__quo );
#endif /* __USE_ISOC99 */

/* Manipulation functions */

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI significand( _LIBIMF_DOUBLE __x );
#endif
#if !defined(__unix__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI significandf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI significandl( _LIBIMF_XDOUBLE __x );
#endif

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI copysign( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI copysignf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI nextafter( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI nextafterf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

#endif  /*!__unix__ && !__APPLE__*/

#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI nexttoward( _LIBIMF_DOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI nexttowardf( _LIBIMF_FLOAT __x, _LIBIMF_XDOUBLE __y );
#endif /* __USE_ISOC99 */

/* Maximum, minimum, and positive difference functions */

#if !defined (__APPLE__) && !(defined(__unix__) && defined(__USE_ISOC99))
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI fdim( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI fdimf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI fmax( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI fmaxf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI fmin( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI fminf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );

/* Floating multiply-add */

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI fma( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y, _LIBIMF_DOUBLE __z );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI fmaf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y, _LIBIMF_FLOAT __z );
#endif /* __USE_ISOC99 */

/* Other - special functions */

#if !defined (__APPLE__)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI annuity( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI compound( _LIBIMF_DOUBLE __x, _LIBIMF_DOUBLE __y );
#endif /* !__APPLE__ */

_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI annuityf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI annuityl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );

_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI compoundf( _LIBIMF_FLOAT __x, _LIBIMF_FLOAT __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI compoundl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );

#if !defined(__unix__)
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI j0f( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI j1f( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI jnf( _LIBIMF_INT __n, _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI y0f( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI y1f( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI ynf( _LIBIMF_INT __n, _LIBIMF_FLOAT __x );
#endif  /* !__unix__ */

#if !(defined(__APPLE__) && !defined(_ANSI_SOURCE)) && !defined(__unix__)

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI j0( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI j1( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI jn( _LIBIMF_INT __n, _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI y0( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI y1( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI yn( _LIBIMF_INT __n, _LIBIMF_DOUBLE __x );

#endif  /*!__unix__ && !__APPLE__*/

#if defined(__APPLE__)
#if defined(_ANSI_SOURCE) || defined(_POSIX_C_SOURCE)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI gamma( _LIBIMF_DOUBLE __x );
#if defined(_XOPEN_SOURCE)
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI significand( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI gamma_r( _LIBIMF_DOUBLE __x, _LIBIMF_INT *__signgam );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI lgammaf_r( _LIBIMF_FLOAT __x, _LIBIMF_INT *__signgam );
#endif /* _XOPEN_SOURCE */
#endif /* _ANSI_SOURCE || _POSIX_C_SOURCE */
#endif /* __APPLE__ */

#if !defined(__unix__)
#if !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI acosl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI asinl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atanl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atan2l( _LIBIMF_XDOUBLE __y, _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cosl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI sinl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI tanl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI acoshl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI asinhl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI atanhl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI coshl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI sinhl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI tanhl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI expl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI expm1l( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI exp2l( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI frexpl( _LIBIMF_XDOUBLE __x, _LIBIMF_INT *__exp );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI ldexpl( _LIBIMF_XDOUBLE __x, _LIBIMF_INT __exp );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI scalbnl( _LIBIMF_XDOUBLE __x, _LIBIMF_INT __n );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI scalblnl( _LIBIMF_XDOUBLE __x, _LIBIMF_LONGINT __n );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI logl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI log10l( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI log2l( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI log1pl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI logbl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_INT      _LIBIMF_PUBAPI ilogbl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI modfl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE *__iptr );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cbrtl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fabsl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI hypotl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI powl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI sqrtl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI erfl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI erfcl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI lgammal( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI tgammal( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI ceill( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI floorl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI nearbyintl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI rintl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lrintl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llrintl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI roundl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGINT  _LIBIMF_PUBAPI lroundl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_LONGLONG _LIBIMF_PUBAPI llroundl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI truncl( _LIBIMF_XDOUBLE __x );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fmodl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI remainderl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI remquol( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y, _LIBIMF_INT *__quo );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI copysignl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI nextafterl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI nexttowardl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fdiml( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fmaxl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fminl( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI fmal( _LIBIMF_XDOUBLE __x, _LIBIMF_XDOUBLE __y, _LIBIMF_XDOUBLE __z );
#endif
#endif


#if (__IMFLONGDOUBLE == 64)	/* MS compatibility */
# define acosdl       acosd
# define acoshl       acosh
# define acosl        acos
# define annuityl     annuity
# define asindl       asind
# define asinhl       asinh
# define asinl        asin
# define atan2dl      atan2d
# define atan2l       atan2
# define atand2l      atand2
# define atandl       atand
# define atanhl       atanh
# define atanl        atan
# define cbrtl        cbrt
# define ceill        ceil
# define compoundl    compound
# define copysignl    copysign
# define cosdl        cosd
# define coshl        cosh
# define cosl         cos
# define cotdl        cotd
# define cotl         cot
# define erfcl        erfc
# define erfl         erf
# define exp10l       exp10
# define exp2l        exp2
# define expl         exp
# define expm1l       expm1
# define fabsl        fabs
# define fdiml        fdim
# define floorl       floor
# define fmal         fma
# define fmaxl        fmax
# define fminl        fmin
# define fmodl        fmod
# define frexpl       frexp
# define gammal       gamma
# define gammal_r     gamma_r
# define hypotl       hypot
# define ilogbl       ilogb
# define invsqrtl     invsqrt
# define  fpclassifyl  __fpclassify
# define  isfinitel    __finite
# define  isinfl       __isinf
# define  isnanl       __isnan
# define  isnormall    __isnormal
# define  signbitl     __signbit

# define __fpclassifyl __fpclassify
# define __finitel     __finite
# define __isinfl      __isinf
# define __isnanl      __isnan
# define __isnormall   __isnormal
# define __signbitl    __signbit

# define isgreaterl         __isgreater
# define isgreaterequall    __isgreaterequal
# define islessl            __isless
# define islessequall       __islessequal
# define islessgreaterl     __islessgreater
# define isunorderedl       __isunordered
# define __isgreaterl       __isgreater
# define __isgreaterequall  __isgreaterequal
# define __islessl          __isless
# define __islessequall     __islessequal
# define __islessgreaterl   __islessgreater
# define __isunorderedl     __isunordered
# define ldexpl       ldexp
# define lgammal      lgamma
# define lgammal_r    lgamma_r
# define llrintl      llrint
# define llroundl     llround
# define log10l       log10
# define log1pl       log1p
# define log2l        log2
# define logbl        logb
# define logl         log
# define lrintl       lrint
# define lroundl      lround
# define modfl        modf
# define nearbyintl   nearbyint
# define nextafterl   nextafter
# define nexttowardl  nexttoward
# define powl         pow
# define remainderl   remainder
# define remquol      remquo
# define rintl        rint
# define roundl       round
# define scalbl       scalb
# define scalblnl     scalbln
# define scalbnl      scalbn
# define significandl significand
# define sincosdl     sincosd
# define sincosl      sincos
# define sindl        sind
# define sinhcoshl    sinhcosh
# define sinhl        sinh
# define sinl         sin
# define sqrtl        sqrt
# define tandl        tand
# define tanhl        tanh
# define tanl         tan
# define tgammal      tgamma
# define truncl       trunc
#endif /*(__IMFLONGDOUBLE == 64)*/



/*-- Complex functions --*/

#if !defined(__cplusplus)  /* No _Complex or GNU __complex__ types available for C++ */
#if defined(__IMFCOMPLEXON) /* c99 complex support enabled */

# define _LIBIMF_DCOMPLEX _LIBIMF_DOUBLE _Complex
# define _LIBIMF_FCOMPLEX _LIBIMF_FLOAT _Complex
# define _LIBIMF_XCOMPLEX _LIBIMF_XDOUBLE _Complex
# if (!defined (__unix__) && !defined(__APPLE__)) || defined(__PURE_INTEL_C99_HEADERS__)
#  define complex		_Complex
#  define _Complex_I	(1.0iF)
#  undef I
#  define I _Complex_I
# endif

/* Complex trigonometric functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI ccos( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI ccosf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI csin( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI csinf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI ctan( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI ctanf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cacos( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cacosf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI casin( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI casinf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI catan( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI catanf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI carg( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cargf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cis( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cisf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cisl( _LIBIMF_XDOUBLE __x );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cisd( _LIBIMF_DOUBLE __x );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cisdf( _LIBIMF_FLOAT __x );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cisdl( _LIBIMF_XDOUBLE __x );

/* Complex exponential functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cexp( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cexpf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cexp2( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cexp2f( _LIBIMF_FCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cexp2l( _LIBIMF_XCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cexp10( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cexp10f( _LIBIMF_FCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cexp10l( _LIBIMF_XCOMPLEX __z );

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI ccosh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI ccoshf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI csinh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI csinhf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI ctanh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI ctanhf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cacosh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cacoshf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI casinh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI casinhf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI catanh( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI catanhf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

/* Complex logarithmic functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI clog( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI clogf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI clog2( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI clog2f( _LIBIMF_FCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI clog2l( _LIBIMF_XCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI clog10( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI clog10f( _LIBIMF_FCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI clog10l( _LIBIMF_XCOMPLEX __z );

/* Complex power/root/abs functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cpow( _LIBIMF_DCOMPLEX __z, _LIBIMF_DCOMPLEX __c );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cpowf( _LIBIMF_FCOMPLEX __z, _LIBIMF_FCOMPLEX __c );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI csqrt( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI csqrtf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cabs( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cabsf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

/* Other complex functions */

#if !defined(__unix__) && !defined(__APPLE__)

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI conj( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI conjf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DCOMPLEX _LIBIMF_PUBAPI cproj( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FCOMPLEX _LIBIMF_PUBAPI cprojf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI cimag( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI cimagf( _LIBIMF_FCOMPLEX __z );

_LIBIMF_EXT _LIBIMF_DOUBLE   _LIBIMF_PUBAPI creal( _LIBIMF_DCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_FLOAT    _LIBIMF_PUBAPI crealf( _LIBIMF_FCOMPLEX __z );

#endif  /*!__unix__ && !__APPLE__*/

#if (!defined(__unix__) && !defined(__APPLE__))
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI ccosl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI csinl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI ctanl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cacosl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI casinl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI catanl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cargl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cexpl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI ccoshl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI csinhl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI ctanhl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cacoshl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI casinhl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI catanhl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI clogl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cpowl( _LIBIMF_XCOMPLEX __z, _LIBIMF_XCOMPLEX __c );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI csqrtl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cabsl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI conjl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XCOMPLEX _LIBIMF_PUBAPI cprojl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI cimagl( _LIBIMF_XCOMPLEX __z );
_LIBIMF_EXT _LIBIMF_XDOUBLE  _LIBIMF_PUBAPI creall( _LIBIMF_XCOMPLEX __z );

#endif  /*!__unix__ */

#if (__IMFLONGDOUBLE == 64)	/* MS compatibility */
# define cabsl   cabs
# define cacoshl cacosh
# define cacosl  cacos
# define cargl   carg
# define casinhl casinh
# define casinl  casin
# define catanhl catanh
# define catanl  catan
# define ccoshl  ccosh
# define ccosl   ccos
# define cexp10l cexp10
# define cexp2l  cexp2
# define cexpl   cexp
# define cimagl  cimag
# define cisdl   cisd
# define cisl    cis
# define clog10l clog10
# define clog2l  clog2
# define clogl   clog
# define conjl   conj
# define cpowl   cpow
# define cprojl  cproj
# define creall  creal
# define csinhl  csinh
# define csinl   csin
# define csqrtl  csqrt
# define ctanhl  ctanh
# define ctanl   ctan
#endif /*(__IMFLONGDOUBLE == 64)*/

#endif  /*__IMFCOMPLEXON*/
#endif  /*!__cplusplus*/

/* MS compatible exception handling */

/* Exception type passed in the type field of exception struct */

#define _DOMAIN    1 /* argument domain error */
#define _SING      2 /* argument singularity */
#define _OVERFLOW  3 /* overflow range error */
#define _UNDERFLOW 4 /* underflow range error */
#if !defined(__unix__)
#define _TLOSS      5   /* total loss of precision */
#define _PLOSS      6   /* partial loss of precision */
#endif

#if (!defined(__unix__) && !defined(__APPLE__)) || !defined(__MATH_H_INCLUDED)
/* support for abcense and presence of Intel math.h */
typedef struct ____exception {
    _LIBIMF_INT     type;
    _LIBIMF_CCHAR  *name;
    _LIBIMF_DOUBLE  arg1;
    _LIBIMF_DOUBLE  arg2;
    _LIBIMF_DOUBLE  retval;
} ___exception;

#if defined(__unix__) || defined(__APPLE__)
# if defined(__cplusplus)
#  define __exception ____exception   /* map 'struct __exception'  to 'struct ____exception'  */
# else     /*__cplusplus*/
#  define   exceptionf ____exceptionf /* map 'struct   exceptionf' to 'struct ____exceptionf' */
#  define   exceptionl ____exceptionl /* map 'struct   exceptionl' to 'struct ____exceptionl' */
# endif    /*__cplusplus*/
#else /* Win32 or Win64 */
#define _exception ____exception
#define _exceptionf ____exceptionf
#define _exceptionl ____exceptionl
#endif

typedef struct ____exceptionf {
    _LIBIMF_INT    type;
    _LIBIMF_CCHAR *name;
    _LIBIMF_FLOAT  arg1;
    _LIBIMF_FLOAT  arg2;
    _LIBIMF_FLOAT  retval;
} ___exceptionf;

typedef struct ____exceptionl {
    _LIBIMF_INT      type;
    _LIBIMF_CCHAR   *name;
    _LIBIMF_XDOUBLE  arg1;
    _LIBIMF_XDOUBLE  arg2;
    _LIBIMF_XDOUBLE  retval;
} ___exceptionl;

#if !defined(__unix__) && !defined(__APPLE__)
_LIBIMF_EXT _LIBIMF_INT _LIBIMF_PUBAPI matherr( struct ____exception  *__e );
#endif /*!__unix__ && !__APPLE__*/
_LIBIMF_EXT _LIBIMF_INT _LIBIMF_PUBAPI matherrf( struct ____exceptionf *__e );
_LIBIMF_EXT _LIBIMF_INT _LIBIMF_PUBAPI matherrl( struct ____exceptionl *__e );

/* User-installable exception handlers
 *
 *  Static redefinition of matherr() is useful only for statically linked
 *  libraries. When Libm is built as a DLL, the Libm's matherr() is already
 *  loaded into the DLL and (statically) linked.  In this case, the only way
 *  to replace the library default matherr() with your matherr() is to use
 *  the matherr() exchange functions (see description below).
 *
 *  1. In user code, implement your own substitute matherr() function.
 *  2. To install it, call __libm_setusermatherr(), with your
 *     function as an argument. Note that the __libm_setusermatherr()
 *     returns the address of previously defined matherr. If you save
 *     the address, you can use it later to restore the original matherr().
 *  3. Your matherr() will now be installed! Your matherr() will be called
 *     instead of the default matherr().
 */

//typedef _LIBIMF_INT( _LIBIMF_PUBAPI *___pmatherr )( struct ____exception  *__e );
//typedef _LIBIMF_INT( _LIBIMF_PUBAPI *___pmatherrf )( struct ____exceptionf *__e );
//typedef _LIBIMF_INT( _LIBIMF_PUBAPI *___pmatherrl )( struct ____exceptionl *__e );
//
//_LIBIMF_EXT ___pmatherr  _LIBIMF_PUBAPI __libm_setusermatherr( ___pmatherr  __user_matherr );
//_LIBIMF_EXT ___pmatherrf _LIBIMF_PUBAPI __libm_setusermatherrf( ___pmatherrf __user_matherrf );
//_LIBIMF_EXT ___pmatherrl _LIBIMF_PUBAPI __libm_setusermatherrl( ___pmatherrl __user_matherrl );

/* Standard conformance support */

#if (!defined(__unix__) || !defined(__USE_MISC))
typedef enum ___LIB_VERSIONIMF_TYPE {
     _IEEE_ = -1    /* IEEE-like behavior    */
    ,_SVID_         /* SysV, Rel. 4 behavior */
    ,_XOPEN_        /* Unix98                */
    ,_POSIX_        /* Posix                 */
    ,_ISOC_         /* ISO C9X               */
} _LIB_VERSIONIMF_TYPE;
#else
# define _LIB_VERSIONIMF_TYPE _LIB_VERSION_TYPE
#endif

_LIBIMF_EXT _LIB_VERSIONIMF_TYPE _LIBIMF_PUBVAR _LIB_VERSIONIMF;

#endif /* (!__unix__ && !__APPLE__) || !__MATH_H_INCLUDED */

#undef _LIBIMF_EXT
#undef _LIBIMF_PUBAPI
#undef _LIBIMF_PUBVAR
#undef _LIBIMF_LONGLONG
#undef _LIBIMF_LONGINT
#undef _LIBIMF_INT
#undef _LIBIMF_DOUBLE
#undef _LIBIMF_FLOAT
#undef _LIBIMF_XDOUBLE
#undef _LIBIMF_VOID
#undef _LIBIMF_CCHAR
#undef _LIBIMF_DCOMPLEX
#undef _LIBIMF_FCOMPLEX
#undef _LIBIMF_XCOMPLEX

#if defined(__cplusplus)    /* end C linkage */
}
#endif

#endif  /*__MATHIMF_H_INCLUDED*/
