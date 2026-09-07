/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s32 func_8001EAA4(s8 *, s8 *);
extern s32 func_80033BC0(s32);
extern s32 func_800A697C(s32, s32);
extern s32 D_80012090[];
extern u8 D_8001F6F0[];
extern s16 D_8008146C[];
extern void *D_800E3D7C[];

s32 func_8001E660(s8 *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    u8 flag_value;
    flag_value = D_8001F6F0[0];

    if ((flag_value == 0) && (arg3 == 0) && (*(s32 *)0x80012090 == 0)) {
        if (D_8008146C[0] == 12) {
            if (M2C_FIELD(D_800E3D7C[0], u8 *, 0xFB) == 0) {
                *arg0 = 12;
                *arg1 = 4;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 15) {
            if ((func_80033BC0(0x145E) != 0) && (func_80033BC0(0x1460) == 0) && ((func_800A697C(0xD, 1) << 0x10) == 0)) {
                *arg0 = 0xD;
                *arg1 = 1;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 28) {
            if ((func_80033BC0(0xFC3) != 0) && (func_80033BC0(0xFAD) == 0) && ((func_800A697C(1, 8) << 0x10) == 0)) {
                *arg0 = 1;
                *arg1 = 8;
                D_8001F6F0[0] = 1;
                return 1;
            }
        } else if (D_8008146C[0] == 20) {
            if ((func_80033BC0(0xAC) != 0) && (func_80033BC0(0x12C6) == 0) && ((func_800A697C(0xD, 6) << 0x10) == 0)) {
                *arg0 = 0xD;
                *arg1 = 6;
                D_8001F6F0[0] = 1;
                return 1;
            }
        }
        func_8001EAA4(arg0, arg1);
        return 0;
    } else {
        func_8001EAA4(arg0, arg1);
        return 0;
    }
}
