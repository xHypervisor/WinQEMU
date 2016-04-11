
//#include "mathex.h"
//
//float32 rintf (float32 Value)
//{
//	float32 RetVal;
//	__asm
//	{
//		fld Value;
//		frndint;
//		fstp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float32)0.5);
//}
//float64 rint (float64 Value)
//{
//	float64 RetVal;
//	__asm
//	{
//		fld Value;
//		frndint;
//		fstp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float64)0.5);
//}
//
//
//
//int32_t lrintf (float32 Value)
//{
//	int32_t RetVal;
//	__asm
//	{
//		fld Value;
//		fistp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float32)0.5);
//}
//int32_t lrint (float64 Value)
//{
//	int32_t RetVal;
//	__asm
//	{
//		fld Value;
//		fistp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float64)0.5);
//}
//
//int64_t llrintf (float32 Value)
//{
//	int64_t RetVal;
//	__asm
//	{
//		fld Value;
//		fistp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float32)0.5);
//}
//int64_t llrint (float64 Value)
//{
//	int64_t RetVal;
//	__asm
//	{
//		fld Value;
//		fistp RetVal;
//	}
//
//	return RetVal;
//	//return floor(Value + (float64)0.5);
//}
//
//float32 remainderf (float32 l , float32 r)
//{
//	float32 RetVal;
//	__asm
//	{
//		fld r;
//		fld l;
//_label:
//		fprem1;		// Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1)
//		fstsw ax;	// status word to AX
//		sahf;
//		jp	_label;
//		fstp st(1);
//
//		fst RetVal;
//	}
//
//	return RetVal;
//}
//
//float64 remainder (float64 l, float64 r)
//{
//	float64 RetVal;
//	__asm
//	{
//		fld r;
//		fld l;
//_label:
//		fprem1;		// Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1)
//		fstsw ax;	// status word to AX
//		sahf;
//		jp	_label;
//		fstp st(1);
//
//		fst RetVal;
//	}
//
//	return RetVal;
//}
//
//
//#define FE_TONEAREST	0x0000
//#define FE_DOWNWARD	0x0400
//#define FE_UPWARD	0x0800
//#define FE_TOWARDZERO	0x0c00
//
//int fesetround (int mode)
//{
//	unsigned short _cw;
//	if ((mode & ~(FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO))
//		!= 0)
//		return -1;
//
//	__asm
//	{
//		fnstcw _cw;
//	}
//	
//	_cw &= ~(FE_TONEAREST | FE_DOWNWARD | FE_UPWARD | FE_TOWARDZERO);
//	_cw |= mode;
//
//	__asm
//	{
//		fldcw _cw;
//	}
//	return 0;
//}
//
//
//typedef uint8_t bits8;
//typedef int8_t sbits8;
//typedef uint16_t bits16;
//typedef int16_t sbits16;
//typedef uint32_t bits32;
//typedef int32_t sbits32;
//typedef uint64_t bits64;
//typedef int64_t sbits64;
//
//#define LIT64( a ) a##LL
//
//static inline bool float32_is_nan( float32 a )
//{
//    return ( 0xFF000000 <  ( (bits32)a<<1 ) );
//}
//static inline bool float64_is_nan( float64 &a )
//{
//    return ( LIT64( 0xFFE0000000000000 ) < ( (bits64) a<<1 ) );
//}
//static inline bool float64_is_nan( long double &a )
//{
//    return ( LIT64( 0xFFE0000000000000 ) < ( (bits64) a<<1 ) );
//}
//
//typedef struct 
//{
//    uint64_t low;
//    uint16_t high;
//} floatx80_t;
//
//bool isunordered (float32 l, float32 r)
//{
//	return (float32_is_nan (l) || float32_is_nan (r));
//}
//
//bool isunordered (float64 &l, float64 &r)
//{
//	return (float64_is_nan (l) || float64_is_nan (r));
//}
//
//bool isunordered (long double &l, long double &r)
//{
//	return (float64_is_nan (l) || float64_is_nan (r));
//}
//
//static inline bool floatx80_is_nan( floatx80 &v)
//{
//	floatx80_t &a = *((floatx80_t*)&v);
//    return (( a.high & 0x7FFF ) == 0x7FFF ) && (bits64) ( a.low<<1 );
//}
//
//
//bool isunordered (floatx80 &l, floatx80 &r)
//{
//	return (floatx80_is_nan (l) || floatx80_is_nan (r));
//}
//
//floatx80 rintl (floatx80 Value)
//{
//	floatx80 RetVal;
//	__asm
//	{
//		fld Value;
//		frndint;
//		fstp RetVal;
//	}
//
//	return RetVal;
//}
//
//floatx80 remainderl (floatx80 l, floatx80 r)
//{
//	floatx80 RetVal;
//	__asm
//	{
//		fld r;
//		fld l;
//_label:
//		fprem1;		// Replace ST(0) with the IEEE remainder obtained from dividing ST(0) by ST(1)
//		fstsw ax;	// status word to AX
//		sahf;
//		jp	_label;
//		fstp st(1);
//
//		fst RetVal;
//	}
//
//	return RetVal;
//}
//
//int32_t lrintl (floatx80 Value)
//{
//	return Value;
//}
//
//int64_t llrintl (floatx80 Value)
//{
//	return Value;
//}
