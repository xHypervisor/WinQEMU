#ifndef __FLOAT80_PORT_H__
#define __FLOAT80_PORT_H__

#define C3 0x4000;	// 0100000000000000
#define C2 0x400;	// 0000010000000000
#define C0 0x100;	//0000000100000000


#if defined (_MSC_VER) && defined(FLOATX80)

#include <math.h>

typedef int BOOL;

#ifdef _MSC_VER
#pragma pack (push, 16)
#endif
typedef struct floatx80
{
	__int8 m_pBuffer [12];
}floatx80;

#ifdef _MSC_VER
#pragma pack (pop)
#endif


inline floatx80 floatx80_chs_impl (floatx80 * __this)
{
	floatx80 Result;
	__asm
	{
		mov  eax, __this;
		fld  TBYTE PTR [eax];
		fchs;
		fstp TBYTE PTR [Result];
	}

	return Result;
}

#if 0
inline floatx80* floatx80_from_int16 (floatx80 * __this, int16_t r)
{
	__asm
	{
		fild WORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80* floatx80_from_int32 (floatx80 * __this, int32_t r)
{
	__asm
	{
		fild DWORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80* floatx80_from_int64 (floatx80 * __this, int64_t r)
{
	__asm
	{
		fild QWORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80* floatx80_from_float (floatx80 * __this, float r)
{
	__asm
	{
		fld DWORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80 floatx80_from_double (floatx80 * __this, double r)
{
	__asm
	{
		fld QWORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return *__this;
}

inline floatx80 floatx80_from_longdouble_impl (floatx80 * __this, long double r)
{
	__asm
	{
		fld QWORD PTR [r];
		mov  eax, __this;
		fstp TBYTE PTR [eax];
	}

	return *__this;
}
#endif

inline floatx80 floatx80_add_floatx80_impl (floatx80 * __this, floatx80* Value)
{
	floatx80 Result;
	__int8* pBuffer = Value->m_pBuffer;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		faddp  st (1), st (0); // ST (1) = ST (1) + ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_add_double_impl (floatx80 * __this, double Value)
{
	floatx80 Result;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		fld    QWORD PTR [Value];
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		faddp  st (1), st (0); // ST (1) = ST (1) + ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_sub_floatx80_impl (floatx80 * __this, floatx80* Value)
{
	floatx80 Result;
	__int8* pBuffer = Value->m_pBuffer;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		fsubp  st (1), st (0); // ST (1) = ST (1) - ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_sub_double_impl (floatx80 * __this, double Value)
{
	floatx80 Result;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		fld    QWORD PTR [Value];
		fsubp  st (1), st (0); // ST (1) = ST (1) - ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_mul_floatx80_impl (floatx80 * __this, floatx80* Value)
{
	floatx80 Result;
	__int8* pBuffer = Value->m_pBuffer;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		fmulp  st (1), st (0); // ST (1) = ST (1) * ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_div_floatx80_impl (floatx80 * __this, floatx80* Value)
{
	floatx80 Result;
	__int8* pBuffer = Value->m_pBuffer;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		fdivp  st (1), st (0);	// ST (1) = ST (1) /ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}


inline floatx80 floatx80_div_double_impl (floatx80 * __this, double Value)
{
	floatx80 Result;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		fld    QWORD PTR [Value];
		fdivp  st (1), st (0);	// ST (1) = ST (1) /ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_div_longdouble_impl (floatx80 * __this, long double Value)
{
	floatx80 Result;
	__int8* pResultBuffer = Result.m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		fld    QWORD PTR [Value];
		fdivp  st (1), st (0);	// ST (1) = ST (1) /ST (0)
		mov    eax, pResultBuffer;
		fstp   TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80* floatx80_mule_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		fmulp  st (1), st (0); // ST (1) = ST (1) * ST (0)
		mov    eax, __this;
		fstp   TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80* floatx80_adde_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		faddp  st (1), st (0); // ST (1) = ST (1) + ST (0)
		mov    eax, __this;
		fstp   TBYTE PTR [eax];
	}

	return __this;
}

inline floatx80* floatx80_sube_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;
	__asm
	{
		mov    eax, __this;
		fld    TBYTE PTR [eax];
		mov    eax, pBuffer;
		fld    TBYTE PTR [eax];
		fsubp  st (1), st (0); // ST (1) = ST (1) - ST (0)
		mov    eax, __this;
		fstp   TBYTE PTR [eax];
	}

	return __this;
}

inline BOOL floatx80_isequal_floatx80_impl (floatx80 * __this, floatx80* Value)
{
	__int8* pBuffer = Value->m_pBuffer;
	int nResult = 0;

	//
	// The following codes is from Intel C++ Compiler
	//
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		mov eax, pBuffer;
		fld TBYTE PTR [eax];
		fucompp;
		fnstsw ax;
		sahf;
		jp _End;
		je _IS_Equal;
		jmp _End;
_IS_Equal:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isequal_double_impl (floatx80 * __this, double Value)
{
	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		fld QWORD PTR [Value];
		fucompp;
		fnstsw ax;
		sahf;
		jp _End;
		je _IS_Equal;
		jmp _End;
_IS_Equal:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isle_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;
	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		mov eax, pBuffer;
		fld TBYTE PTR [eax];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		jae _LessOrEqual;
		jmp _End;
_LessOrEqual:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isl_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;

	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		mov eax, pBuffer;
		fld TBYTE PTR [eax];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		ja _Less;
		jmp _End;
_Less:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isl_double_impl(floatx80 * __this, double Value)
{
	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		fld QWORD PTR [Value];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		ja _Less;
		jmp _End;
_Less:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isge_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	//return ((*__this > Value) || (*__this == Value));
	//return (((long double)*__this) >= (long double)(*const_cast <floatx80*> (&Value)));
	__int8* pBuffer = Value->m_pBuffer;

	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		mov eax, pBuffer;
		fld TBYTE PTR [eax];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		jbe _GreaterOrEqual;
		jmp _End;
_GreaterOrEqual:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isge_double_impl (floatx80 * __this, double Value)
{
	//return ((*__this > Value) || (*__this == Value));
	//return (((long double)*__this) >= Value);

	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		fld QWORD PTR [Value];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		jbe _GreaterOrEqual;
		jmp _End;
_GreaterOrEqual:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isg_floatx80_impl (floatx80 * __this, floatx80 *Value)
{
	__int8* pBuffer = Value->m_pBuffer;

	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		mov eax, pBuffer;
		fld TBYTE PTR [eax];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		jb _Greater;
		jmp _End;
_Greater:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline BOOL floatx80_isg_double_impl (floatx80 * __this, double Value)
{
	int nResult = 0;
	__asm
	{
		mov eax, __this;
		fld TBYTE PTR [eax];
		fld QWORD PTR [Value];
		fcompp;
		fnstsw ax;
		sahf;
		jp _End;
		jb _Greater;
		jmp _End;
_Greater:
		mov nResult, 1;
_End:
	}

	return (nResult != 0);
}

inline float32 floatx80_to_float32_impl (floatx80 * __this)
{
	float32 Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fstp DWORD PTR [Result];
	}

	return Result;
}

inline long double floatx80_to_longdouble_impl (floatx80 * __this)
{
	long double Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fstp QWORD PTR [Result];
	}

	return Result;
}

inline float64 floatx80_to_float64_impl (floatx80 * __this)
{
	float64 Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fstp QWORD PTR [Result];
	}

	return Result;
}

inline int16_t floatx80_to_int16_impl (floatx80 * __this)
{
	int Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fistp WORD PTR [Result];
	}

	return Result;
}

inline int32_t floatx80_to_int32_impl (floatx80 * __this)
{
	int Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fistp DWORD PTR [Result];
	}

	return Result;
}

inline int64_t floatx80_to_int64_impl (floatx80 * __this)
{
	int64_t Result;
	__asm
	{
		mov eax, __this;
		fld  TBYTE PTR [eax];
		fistp QWORD PTR [Result];
	}

	return Result;
}

inline floatx80 floatx80_from_float_impl (float Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fld DWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_from_double_impl (double Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;

	__asm
	{
		fld QWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_from_longdouble_impl (long double Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fld  QWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_from_int32_impl (int32_t Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fild DWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_from_uint32_impl (uint32_t Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fild DWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}
	return Result;
}

inline floatx80 floatx80_from_int64_impl (int64_t Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fild  QWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}


inline floatx80 floatx80_from_uint64_impl (uint64_t Value)
{
	floatx80 Result;
	__int8* pBuffer = Result.m_pBuffer;
	__asm
	{
		fild  QWORD PTR [Value];
		mov eax, pBuffer;
		fstp TBYTE PTR [eax];
	}

	return Result;
}

inline floatx80 floatx80_fabsl_impl (floatx80 *value)
{
	return floatx80_from_longdouble_impl (fabs (floatx80_to_float64_impl (value)));
}

inline floatx80 floatx80_fabs80_impl (floatx80 *value)
{
	return floatx80_fabsl_impl (value);
}

inline floatx80 floatx80_sqrtl_impl (floatx80 *value)
{
	return floatx80_from_longdouble_impl (sqrt (floatx80_to_float64_impl (value)));
}

inline floatx80 floatx80_cosl_impl(floatx80 *value)
{
	return floatx80_from_longdouble_impl (cos (floatx80_to_float64_impl (value)));
}

inline floatx80 floatx80_sinl_impl(floatx80 *value)
{
	return floatx80_from_longdouble_impl (sin (floatx80_to_float64_impl (value)));
}
inline floatx80 floatx80_ldexp_impl(floatx80 *_X, int _Y)
{
	return floatx80_from_longdouble_impl (ldexp (floatx80_to_float64_impl (_X), _Y));
}
inline floatx80 floatx80_logl_impl(floatx80 *_X)
{
	return floatx80_from_longdouble_impl (logl (floatx80_to_float64_impl (_X)));
}
inline floatx80 floatx80_tanl_impl(floatx80 *_X)
{
	return floatx80_from_longdouble_impl (tanl (floatx80_to_float64_impl (_X)));
}
inline floatx80 floatx80_floorl_impl(floatx80 *_X)
{
	return floatx80_from_longdouble_impl (floorl (floatx80_to_float64_impl (_X)));
}
inline floatx80 floatx80_floor80_impl(floatx80 *_X)
{
	return floatx80_from_longdouble_impl (floorl (floatx80_to_float64_impl (_X)));
}
inline floatx80 floatx80_ceill_impl(floatx80 *_X)
{
	return floatx80_from_longdouble_impl (ceill (floatx80_to_float64_impl (_X)));
}
inline floatx80 floatx80_atan2l_impl(floatx80 *_X, floatx80 *_Y)
{
	return floatx80_from_longdouble_impl (atan2l (floatx80_to_float64_impl (_X), floatx80_to_float64_impl (_Y)));
}

inline floatx80 floatx80_powl_impl (floatx80 *_X, floatx80 *_Y)
{
	return floatx80_from_longdouble_impl (powl (floatx80_to_float64_impl (_X), floatx80_to_float64_impl (_Y)));
}

inline floatx80 floatx80_rintl_impl (floatx80 *_X)
{
	floatx80 Result;

	__asm
	{
		mov  eax, _X;
		fld  TBYTE PTR [eax];
		frndint;
		fstp TBYTE PTR [Result];
	}

	return Result;
}

#endif

#endif