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


inline floatx80 fx80_chs (floatx80 * __this)
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

inline floatx80 fx80_from_longdouble (floatx80 * __this, long double r)
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

inline floatx80 fx80_add_fx80 (floatx80 * __this, floatx80* Value)
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

inline floatx80 fx80_add_double (floatx80 * __this, double Value)
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

inline floatx80 fx80_sub_fx80 (floatx80 * __this, floatx80* Value)
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

inline floatx80 fx80_sub_double (floatx80 * __this, double Value)
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

inline floatx80 fx80_mul_x80 (floatx80 * __this, floatx80* Value)
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

inline floatx80 fx80_div_fx80 (floatx80 * __this, floatx80* Value)
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


inline floatx80 fx80_div_double (floatx80 * __this, double Value)
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

inline floatx80 fx80_div_longdouble (floatx80 * __this, long double Value)
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

inline floatx80* fx80_mule_fx80 (floatx80 * __this, floatx80 *Value)
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

inline floatx80* fx80_adde_fx80 (floatx80 * __this, floatx80 *Value)
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

inline floatx80* fx80_sube_fx80 (floatx80 * __this, floatx80 *Value)
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

inline BOOL fx80_isequal_fx80 (floatx80 * __this, floatx80* Value)
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

inline BOOL fx80_isequal_double (floatx80 * __this, double Value)
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

inline BOOL fx80_isle_fx80 (floatx80 * __this, floatx80 *Value)
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

inline BOOL fx80_isl_fx80 (floatx80 * __this, floatx80 *Value)
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

inline BOOL fx80_isl_double(floatx80 * __this, double Value)
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

inline BOOL fx80_isge_fx80 (floatx80 * __this, floatx80 *Value)
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

inline BOOL fx80_isge_double (floatx80 * __this, double Value)
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

inline BOOL fx80_isg_fx80 (floatx80 * __this, floatx80 *Value)
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

inline BOOL fx80_isg_double (floatx80 * __this, double Value)
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

inline float32 fx80_to_f32 (floatx80 * __this)
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

inline long double fx80_to_longdouble (floatx80 * __this)
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

inline float64 fx80_to_f64 (floatx80 * __this)
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

inline int16_t fx80_to_int16 (floatx80 * __this)
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

inline int32_t fx80_to_int32 (floatx80 * __this)
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

inline int64_t fx80_to_int64 (floatx80 * __this)
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

inline floatx80 fx80_from_float (float Value)
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

inline floatx80 fx80_from_double (double Value)
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

inline floatx80 fx80_from_longdouble (long double Value)
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

inline floatx80 fx80_from_int32 (int32_t Value)
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

inline floatx80 fx80_from_uint32 (uint32_t Value)
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

inline floatx80 fx80_from_int64 (int64_t Value)
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


inline floatx80 fx80_from_uint64 (uint64_t Value)
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

inline floatx80 fx80_fabsl (floatx80 *value)
{
	return fx80_from_longdouble (fabs (fx80_to_f64 (value)));
}

inline floatx80 fx80_fabs80 (floatx80 *value)
{
	return fx80_fabsl (value);
}

inline floatx80 fx80_sqrtl (floatx80 *value)
{
	return fx80_from_longdouble (sqrt (fx80_to_f64 (value)));
}

inline floatx80 fx80_cosl(floatx80 *value)
{
	return fx80_from_longdouble (cos (fx80_to_f64 (value)));
}

inline floatx80 fx80_sinl(floatx80 *value)
{
	return fx80_from_longdouble (sin (fx80_to_f64 (value)));
}
inline floatx80 fx80_ldexp(floatx80 *_X, int _Y)
{
	return fx80_from_longdouble (ldexp (fx80_to_f64 (_X), _Y));
}
inline floatx80 fx80_logl(floatx80 *_X)
{
	return fx80_from_longdouble (logl (fx80_to_f64 (_X)));
}
inline floatx80 fx80_tanl(floatx80 *_X)
{
	return fx80_from_longdouble (tanl (fx80_to_f64 (_X)));
}
inline floatx80 fx80_floorl(floatx80 *_X)
{
	return fx80_from_longdouble (floorl (fx80_to_f64 (_X)));
}
inline floatx80 fx80_floor80(floatx80 *_X)
{
	return fx80_from_longdouble (floorl (fx80_to_f64 (_X)));
}
inline floatx80 fx80_ceill(floatx80 *_X)
{
	return fx80_from_longdouble (ceill (fx80_to_f64 (_X)));
}
inline floatx80 fx80_atan2l(floatx80 *_X, floatx80 *_Y)
{
	return fx80_from_longdouble (atan2l (fx80_to_f64 (_X), fx80_to_f64 (_Y)));
}

inline floatx80 fx80_powl (floatx80 *_X, floatx80 *_Y)
{
	return fx80_from_longdouble (powl (fx80_to_f64 (_X), fx80_to_f64 (_Y)));
}

inline floatx80 fx80_rintl (floatx80 *_X)
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