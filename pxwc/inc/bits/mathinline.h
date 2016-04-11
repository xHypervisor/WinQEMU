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

#ifndef _MATH_
# error "Never use <pvt/mathinline.h> directly; include <math.h> instead."
#endif

#if defined __USE_ISOC99 && defined __GNUC__ && __GNUC__ >= 2
# if __GNUC_PREREQ (2, 97)
/* GCC 2.97 and up have builtins that actually can be used.  */
#  define isgreater(x, y) __builtin_isgreater (x, y)
#  define isgreaterequal(x, y) __builtin_isgreaterequal (x, y)
#  define isless(x, y) __builtin_isless (x, y)
#  define islessequal(x, y) __builtin_islessequal (x, y)
#  define islessgreater(x, y) __builtin_islessgreater (x, y)
#  define isunordered(x, y) __builtin_isunordered (x, y)
# else
/* ISO C99 defines some macros to perform unordered comparisons.  The
   ix87 FPU supports this with special opcodes and we should use them.
   These must not be inline functions since we have to be able to handle
   all floating-point types.  */
#  ifdef __i686__
/* For the PentiumPro and more recent processors we can provide
   better code.  */
#   define isgreater(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; seta %%al"           \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");        \
  __result; })
#   define isgreaterequal(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; setae %%al"            \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");        \
  __result; })

#   define isless(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; seta %%al"           \
     : "=a" (__result) : "u" (x), "t" (y) : "cc", "st");        \
  __result; })

#   define islessequal(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; setae %%al"            \
     : "=a" (__result) : "u" (x), "t" (y) : "cc", "st");        \
  __result; })

#   define islessgreater(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; setne %%al"            \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");        \
  __result; })

#   define isunordered(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucomip %%st(1), %%st; setp %%al"           \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st");        \
  __result; })
#  else
/* This is the dumb, portable code for i386 and above.  */
#   define isgreater(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; testb $0x45, %%ah; setz %%al"        \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
  __result; })

#   define isgreaterequal(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; testb $0x05, %%ah; setz %%al"        \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
  __result; })

#   define isless(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; testb $0x45, %%ah; setz %%al"        \
     : "=a" (__result) : "u" (x), "t" (y) : "cc", "st", "st(1)"); \
  __result; })

#   define islessequal(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; testb $0x05, %%ah; setz %%al"        \
     : "=a" (__result) : "u" (x), "t" (y) : "cc", "st", "st(1)"); \
  __result; })

#   define islessgreater(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; testb $0x44, %%ah; setz %%al"        \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
  __result; })

#   define isunordered(x, y) \
     ({ register char __result;                 \
  __asm__ ("fucompp; fnstsw; sahf; setp %%al"           \
     : "=a" (__result) : "u" (y), "t" (x) : "cc", "st", "st(1)"); \
  __result; })
#  endif /* __i686__ */
# endif /* GCC 2.97 */

#endif


/* The gcc, version 2.7 or below, has problems with all this inlining
   code.  So disable it for this version of the compiler.  */
#if defined __GNUC__ && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 7))

#if (!defined __NO_MATH_INLINES && defined __OPTIMIZE__)

/* A macro to define float, double, and long double versions of various
   math functions for the ix87 FPU.  FUNC is the function name (which will
   be suffixed with f and l for the float and long double version,
   respectively).  OP is the name of the FPU operation.  */

#if defined __USE_MISC || defined __USE_UNIX98
# define __INLINE_mathop(func, op) \
  __INLINE_mathop_ (double, func, op)               \
  __INLINE_mathop_ (float, __CONCAT(func,f), op)            \
  __INLINE_mathop_ (long double, __CONCAT(func,l), op)
#else
# define __INLINE_mathop(func, op) \
  __INLINE_mathop_ (double, func, op)
#endif

#define __INLINE_mathop_(float_type, func, op) \
  __INLINE_mathop_decl_ (float_type, func, op, "0" (__x))


#if defined __USE_MISC || defined __USE_UNIX98
# define __INLINE_mathop_decl(func, op, params...) \
  __INLINE_mathop_decl_ (double, func, op, params)            \
  __INLINE_mathop_decl_ (float, __CONCAT(func,f), op, params)         \
  __INLINE_mathop_decl_ (long double, __CONCAT(func,l), op, params)
#else
# define __INLINE_mathop_decl(func, op, params...) \
  __INLINE_mathop_decl_ (double, func, op, params)
#endif

#define __INLINE_mathop_decl_(float_type, func, op, params...) \
  __EXTERN_INLINE float_type func (float_type) __THROW; \
  __EXTERN_INLINE float_type func (float_type __x) __THROW \
  { \
    register float_type __result; \
    __asm __volatile__ (op : "=t" (__result) : params); \
    return __result; \
  }


#if defined __USE_MISC || defined __USE_UNIX98
# define __INLINE_mathcode(func, arg, code) \
  __INLINE_mathcode_ (double, func, arg, code)              \
  __INLINE_mathcode_ (float, __CONCAT(func,f), arg, code)         \
  __INLINE_mathcode_ (long double, __CONCAT(func,l), arg, code)
# define __INLINE_mathcode2(func, arg1, arg2, code) \
  __INLINE_mathcode2_ (double, func, arg1, arg2, code)            \
  __INLINE_mathcode2_ (float, __CONCAT(func,f), arg1, arg2, code)       \
  __INLINE_mathcode2_ (long double, __CONCAT(func,l), arg1, arg2, code)
# define __INLINE_mathcode3(func, arg1, arg2, arg3, code) \
  __INLINE_mathcode3_ (double, func, arg1, arg2, arg3, code)          \
  __INLINE_mathcode3_ (float, __CONCAT(func,f), arg1, arg2, arg3, code)       \
  __INLINE_mathcode3_ (long double, __CONCAT(func,l), arg1, arg2, arg3, code)
#else
# define __INLINE_mathcode(func, arg, code) \
  __INLINE_mathcode_ (double, func, (arg), code)
# define __INLINE_mathcode2(func, arg1, arg2, code) \
  __INLINE_mathcode2_ (double, func, arg1, arg2, code)
# define __INLINE_mathcode3(func, arg1, arg2, arg3, code) \
  __INLINE_mathcode3_ (double, func, arg1, arg2, arg3, code)
#endif

#define __INLINE_mathcode_(float_type, func, arg, code) \
  __EXTERN_INLINE float_type func (float_type) __THROW; \
  __EXTERN_INLINE float_type func (float_type arg) __THROW \
  { \
    code; \
  }

#define __INLINE_mathcode2_(float_type, func, arg1, arg2, code) \
  __EXTERN_INLINE float_type func (float_type, float_type) __THROW; \
  __EXTERN_INLINE float_type func (float_type arg1, float_type arg2) __THROW \
  { \
    code; \
  }

#define __INLINE_mathcode3_(float_type, func, arg1, arg2, arg3, code) \
  __EXTERN_INLINE float_type func (float_type, float_type, float_type) __THROW; \
  __EXTERN_INLINE float_type func (float_type arg1, float_type arg2, float_type arg3) __THROW \
  { \
    code; \
  }
#endif


#if !defined __NO_MATH_INLINES && defined __OPTIMIZE__
/* Miscellaneous functions */

__INLINE_mathcode (sgn, __x, \
  return __x == 0.0 ? 0.0 : (__x > 0.0 ? 1.0 : -1.0))

__INLINE_mathcode (pow2, __x, \
  register long double __value;                 \
  register long double __exponent;                \
  __extension__ long long int __p = (long long int) __x;          \
  if (__x == (long double) __p)                 \
    {                       \
      __asm __volatile__                  \
  ("fscale"                   \
   : "=t" (__value) : "0" (1.0), "u" (__x));            \
      return __value;                   \
    }                       \
  __asm __volatile__                    \
    ("fld %%st(0)\n\t"                  \
     "frndint     # int(x)\n\t"             \
     "fxch\n\t"                     \
     "fsub  %%st(1)   # fract(x)\n\t"             \
     "f2xm1     # 2^(fract(x)) - 1\n\t"           \
     : "=t" (__value), "=u" (__exponent) : "0" (__x));            \
  __value += 1.0;                   \
  __asm __volatile__                    \
    ("fscale"                     \
     : "=t" (__value) : "0" (__value), "u" (__exponent));         \
  return __value)

#define __sincos_code \
  register long double __cosr;                  \
  register long double __sinr;                  \
  __asm __volatile__                    \
    ("fsincos\n\t"                    \
     : "=t" (__cosr), "=u" (__sinr) : "0" (__x));           \
  *__sinx = __sinr;                   \
  *__cosx = __cosr

__EXTERN_INLINE void sincos (double __x, double *__sinx, double *__cosx) __THROW;
__EXTERN_INLINE void
sincos (double __x, double *__sinx, double *__cosx) __THROW
{
  __sincos_code;
}

__EXTERN_INLINE void sincosf (float __x, float *__sinx, float *__cosx) __THROW;
__EXTERN_INLINE void
sincosf (float __x, float *__sinx, float *__cosx) __THROW
{
  __sincos_code;
}

__EXTERN_INLINE void __sincosl (long double __x, long double *__sinx, long double *__cosx) __THROW;
__EXTERN_INLINE void
__sincosl (long double __x, long double *__sinx, long double *__cosx) __THROW
{
  __sincos_code;
}


/* Optimized inline implementation, sometimes with reduced precision
   and/or argument range.  */

#define __expm1_code \
  register long double __value;                 \
  register long double __exponent;                \
  register long double __temp;                  \
  __asm __volatile__                    \
    ("fldl2e      # e^x - 1 = 2^(x * log2(e)) - 1\n\t"        \
     "fmul  %%st(1)   # x * log2(e)\n\t"            \
     "fst %%st(1)\n\t"                  \
     "frndint     # int(x * log2(e))\n\t"           \
     "fxch\n\t"                     \
     "fsub  %%st(1)   # fract(x * log2(e))\n\t"         \
     "f2xm1     # 2^(fract(x * log2(e))) - 1\n\t"       \
     "fscale      # 2^(x * log2(e)) - 2^(int(x * log2(e)))\n\t" \
     : "=t" (__value), "=u" (__exponent) : "0" (__x));            \
  __asm __volatile__                    \
    ("fscale      # 2^int(x * log2(e))\n\t"         \
     : "=t" (__temp) : "0" (1.0), "u" (__exponent));            \
  __temp -= 1.0;                    \
  return __temp + __value
__INLINE_mathcode_ (long double, __expm1l, __x, __expm1_code)


#define __exp_code \
  register long double __value;                 \
  register long double __exponent;                \
  __asm __volatile__                    \
    ("fldl2e      # e^x = 2^(x * log2(e))\n\t"          \
     "fmul  %%st(1)   # x * log2(e)\n\t"            \
     "fst %%st(1)\n\t"                  \
     "frndint     # int(x * log2(e))\n\t"           \
     "fxch\n\t"                     \
     "fsub  %%st(1)   # fract(x * log2(e))\n\t"         \
     "f2xm1     # 2^(fract(x * log2(e))) - 1\n\t"       \
     : "=t" (__value), "=u" (__exponent) : "0" (__x));            \
  __value += 1.0;                   \
  __asm __volatile__                    \
    ("fscale"                     \
     : "=t" (__value) : "0" (__value), "u" (__exponent));         \
  return __value
__INLINE_mathcode (exp, __x, __exp_code)
__INLINE_mathcode_ (long double, __expl, __x, __exp_code)


__INLINE_mathcode (tan, __x, \
  register long double __value;                 \
  register long double __value2 __attribute__ ((__unused__));         \
  __asm __volatile__                    \
    ("fptan"                      \
     : "=t" (__value2), "=u" (__value) : "0" (__x));            \
  return __value)


#define __atan2_code \
  register long double __value;                 \
  __asm __volatile__                    \
    ("fpatan\n\t"                   \
     : "=t" (__value) : "0" (__x), "u" (__y) : "st(1)");          \
  return __value
__INLINE_mathcode2 (atan2, __y, __x, __atan2_code)
__INLINE_mathcode2_ (long double, __atan2l, __y, __x, __atan2_code)


__INLINE_mathcode2 (fmod, __x, __y, \
  register long double __value;     \
  __asm __volatile__                \
    ("1:  fprem\n\t"                \
     "fnstsw  %%ax\n\t"             \
     "sahf\n\t"                     \
     "jp  1b"                       \
     : "=t" (__value) : "0" (__x), "u" (__y) : "ax", "cc");         \
  return __value)


__INLINE_mathcode2 (pow, __x, __y, \
  register long double __value;                 \
  register long double __exponent;                \
  __extension__ long long int __p = (long long int) __y;          \
  if (__x == 0.0 && __y > 0.0)                  \
    return 0.0;                     \
  if (__y == (double) __p)                  \
    {                       \
      long double __r = 1.0;                  \
      if (__p == 0)                   \
  return 1.0;                   \
      if (__p < 0)                    \
  {                     \
    __p = -__p;                   \
    __x = 1.0 / __x;                  \
  }                     \
      while (1)                     \
  {                     \
    if (__p & 1)                    \
      __r *= __x;                   \
    __p >>= 1;                    \
    if (__p == 0)                   \
      return __r;                   \
    __x *= __x;                   \
  }                     \
      /* NOTREACHED */                    \
    }                       \
  __asm __volatile__                    \
    ("fyl2x" : "=t" (__value) : "0" (__x), "u" (1.0) : "st(1)");        \
  __asm __volatile__                    \
    ("fmul  %%st(1)   # y * log2(x)\n\t"            \
     "fst %%st(1)\n\t"                  \
     "frndint     # int(y * log2(x))\n\t"           \
     "fxch\n\t"                     \
     "fsub  %%st(1)   # fract(y * log2(x))\n\t"         \
     "f2xm1     # 2^(fract(y * log2(x))) - 1\n\t"       \
     : "=t" (__value), "=u" (__exponent) : "0" (__y), "1" (__value));       \
  __value += 1.0;                   \
  __asm __volatile__                    \
    ("fscale"                     \
     : "=t" (__value) : "0" (__value), "u" (__exponent));         \
  return __value)


__INLINE_mathop (sqrt, "fsqrt")
__INLINE_mathop_ (long double, __sqrtl, "fsqrt")

#if defined __GNUC__ && (__GNUC__ > 2 || __GNUC__ == 2 && __GNUC_MINOR__ >= 8)
__INLINE_mathcode_ (double, fabs, __x, return __builtin_fabs (__x))
__INLINE_mathcode_ (float, fabsf, __x, return __builtin_fabsf (__x))
__INLINE_mathcode_ (long double, fabsl, __x, return __builtin_fabsl (__x))
__INLINE_mathcode_ (long double, __fabsl, __x, return __builtin_fabsl (__x))
#else
__INLINE_mathop (fabs, "fabs")
__INLINE_mathop_ (long double, __fabsl, "fabs")
#endif

/* The argument range of this inline version is reduced.  */
__INLINE_mathop (sin, "fsin")
/* The argument range of this inline version is reduced.  */
__INLINE_mathop (cos, "fcos")

__INLINE_mathop (atan, "fld1; fpatan")
__INLINE_mathop (log, "fldln2; fxch; fyl2x")
__INLINE_mathop (log10, "fldlg2; fxch; fyl2x")

__INLINE_mathcode (asin, __x, return __atan2l (__x, __sqrtl (1.0 - __x * __x)))
__INLINE_mathcode (acos, __x, return __atan2l (__sqrtl (1.0 - __x * __x), __x))

__INLINE_mathcode_ (long double, __sgn1l, __x, return __x >= 0.0 ? 1.0 : -1.0)


/* The argument range of the inline version of sinhl is slightly reduced.  */
__INLINE_mathcode (sinh, __x, \
  register long double __exm1 = __expm1l (__fabsl (__x));         \
  return 0.5 * (__exm1 / (__exm1 + 1.0) + __exm1) * __sgn1l (__x))

__INLINE_mathcode (cosh, __x, \
  register long double __ex = __expl (__x);             \
  return 0.5 * (__ex + 1.0 / __ex))

__INLINE_mathcode (tanh, __x, \
  register long double __exm1 = __expm1l (-__fabsl (__x + __x));        \
  return __exm1 / (__exm1 + 2.0) * __sgn1l (-__x))


__INLINE_mathcode (floor, __x, \
  register long double __value;                 \
  __volatile const unsigned short int __cw = 0x077f;               \
  __volatile unsigned short int __cwtmp;              \
  __asm __volatile ("fnstcw %0" : "=m" (__cwtmp));             \
  __asm __volatile ("fldcw %0" : : "m" (__cw));            \
  __asm __volatile ("frndint" : "=t" (__value) : "0" (__x));          \
  __asm __volatile ("fldcw %0" : : "m" (__cwtmp));             \
  return __value)

__INLINE_mathcode (ceil, __x, \
  register long double __value;                 \
  __volatile const unsigned short int __cw = 0x0b7f;               \
  __volatile unsigned short int __cwtmp;              \
  __asm __volatile ("fnstcw %0" : "=m" (__cwtmp));             \
  __asm __volatile ("fldcw %0" : : "m" (__cw));            \
  __asm __volatile ("frndint" : "=t" (__value) : "0" (__x));          \
  __asm __volatile ("fldcw %0" : : "m" (__cwtmp));             \
  return __value)

#ifdef __i686__

# define __frexp_code \
  register long double __value; \
  int __exp; \
  register char __is_nunordered; \
  __asm__ ("fucomip %%st(1), %%st; setnp %%al" \
     : "=a" (__is_nunordered) : "u" (0.0), "t" (__x) : "cc", "st"); \
  if (__is_nunordered) { \
    __asm __volatile__ ("fxtract; fxch; fld1; faddp; fistpl %1" : "=t" (__value), "=m" (*__expp) : "0" (__x)); \
    __value *= 0.5; \
  } else { \
    __value = 0.0; *__expp = 0; \
  } \
  return __value

#else

# define __frexp_code \
  register long double __value; \
  int __exp; \
  register char __is_nunordered; \
  __asm__ ("fucomp; fnstsw; sahf; setnp %%al" \
     : "=a" (__is_nunordered) : "u" (0.0), "t" (__x) : "cc", "st"); \
  if (__is_nunordered) { \
    __asm __volatile__ ("fxtract; fxch; fld1; faddp; fistpl %1" : "=t" (__value), "=m" (*__expp) : "0" (__x)); \
    __value *= 0.5; \
  } else { \
    __value = 0.0; *__expp = 0; \
  } \
  return __value

#endif

__EXTERN_INLINE double frexp (double __x, int *__exp) __THROW;
__EXTERN_INLINE double
frexp (double __x, int *__expp) __THROW
{
  __frexp_code;
}

#define __ldexp_code \
  register long double __value; \
  __asm __volatile__ ("fscale" : "=t" (__value) : "0" (__x), "u" ((long double) __exp)); \
  return __value

__EXTERN_INLINE double ldexp (double __x, int __exp) __THROW;
__EXTERN_INLINE double
ldexp (double __x, int __exp) __THROW
{
  __ldexp_code;
}


/* Optimized versions for some non-standardized functions.  */
#if defined __USE_UNIX98 || defined __USE_MISC

__INLINE_mathcode (expm1, __x, __expm1_code)

/* We cannot rely on M_SQRT being defined.  So we do it for ourself
   here.  */
# define __M_SQRT2  1.41421356237309504880L /* sqrt(2) */

__INLINE_mathcode (log1p, __x, \
  register long double __value;                 \
  if (__fabsl (__x) >= 1.0 - 0.5 * __M_SQRT2)             \
    __value = logl (1.0 + __x);                 \
  else                        \
    __asm __volatile__                    \
      ("fldln2\n\t"                   \
       "fxch\n\t"                   \
       "fyl2xp1"                    \
       : "=t" (__value) : "0" (__x));               \
  return __value)


/* The argument range of the inline version of asinhl is slightly reduced.  */
__INLINE_mathcode (asinh, __x, \
  register long double  __y = __fabsl (__x);              \
  return (log1pl (__y * __y / (__sqrtl (__y * __y + 1.0) + 1.0) + __y)        \
    * __sgn1l (__x)))

__INLINE_mathcode (acosh, __x, \
  return logl (__x + __sqrtl (__x - 1.0) * __sqrtl (__x + 1.0)))

__INLINE_mathcode (atanh, __x, \
  register long double __y = __fabsl (__x);             \
  return -0.5 * log1pl (-(__y + __y) / (1.0 + __y)) * __sgn1l (__x))

/* The argument range of the inline version of hypotl is slightly reduced.  */
__INLINE_mathcode2 (hypot, __x, __y, return __sqrtl (__x * __x + __y * __y))

__INLINE_mathcode(logb, __x, \
  register long double __value;                 \
  register long double __junk;                  \
  __asm __volatile__                    \
    ("fxtract\n\t"                    \
     : "=t" (__junk), "=u" (__value) : "0" (__x));            \
  return __value)

#endif

#ifdef __USE_UNIX98
__INLINE_mathop(log2, "fld1; fxch; fyl2x")

__EXTERN_INLINE float frexpf (float __x, int *__exp) __THROW;
__EXTERN_INLINE float
frexpf (float __x, int *__expp) __THROW
{
  __frexp_code;
}

__EXTERN_INLINE long double frexpl (long double __x, int *__exp) __THROW;
__EXTERN_INLINE long double
frexpl (long double __x, int *__expp) __THROW
{
  __frexp_code;
}

__EXTERN_INLINE float ldexpf (float __x, int __exp) __THROW;
__EXTERN_INLINE float
ldexpf (float __x, int __exp) __THROW
{
  __ldexp_code;
}

__EXTERN_INLINE long double ldexpl (long double __x, int __exp) __THROW;
__EXTERN_INLINE long double
ldexpl (long double __x, int __exp) __THROW
{
  __ldexp_code;
}

__INLINE_mathcode3 (fma, __x, __y, __z, return (__x * __y) + __z)

__INLINE_mathop(rint, "frndint")

#define __lrint_code \
  long int __lrintres;                    \
  __asm__ __volatile__                    \
    ("fistpl %0"                    \
     : "=m" (__lrintres) : "t" (__x) : "st");             \
  return __lrintres
__EXTERN_INLINE long int
lrintf (float __x) __THROW
{
  __lrint_code;
}
__EXTERN_INLINE long int
lrint (double __x) __THROW
{
  __lrint_code;
}
__EXTERN_INLINE long int
lrintl (long double __x) __THROW
{
  __lrint_code;
}
#undef __lrint_code

#define __llrint_code \
  long long int __llrintres;                  \
  __asm__ __volatile__                    \
    ("fistpll %0"                   \
     : "=m" (__llrintres) : "t" (__x) : "st");              \
  return __llrintres
__EXTERN_INLINE long long int
llrintf (float __x) __THROW
{
  __llrint_code;
}
__EXTERN_INLINE long long int
llrint (double __x) __THROW
{
  __llrint_code;
}
__EXTERN_INLINE long long int
llrintl (long double __x) __THROW
{
  __llrint_code;
}
#undef __llrint_code

#endif


#ifdef __USE_MISC

__INLINE_mathcode2 (drem, __x, __y, \
  register double __value;                  \
  register int __clobbered;                 \
  __asm __volatile__                    \
    ("1:  fprem1\n\t"                 \
     "fstsw %%ax\n\t"                 \
     "sahf\n\t"                     \
     "jp  1b"                   \
     : "=t" (__value), "=&a" (__clobbered) : "0" (__x), "u" (__y) : "cc");    \
  return __value)


/* Miscellaneous functions */

__INLINE_mathcode (__coshm1, __x, \
  register long double __exm1 = __expm1l (__fabsl (__x));         \
  return 0.5 * (__exm1 / (__exm1 + 1.0)) * __exm1)

__INLINE_mathcode (__acosh1p, __x, \
  return log1pl (__x + __sqrtl (__x) * __sqrtl (__x + 2.0)))

#endif /* __USE_MISC  */

/* Undefine some of the large macros which are not used anymore.  */
#undef __expm1_code
#undef __exp_code
#undef __atan2_code
#undef __sincos_code

#endif /* __NO_MATH_INLINES  */

#endif /* __GNUC__  */
