#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
s32 func_800A45D8();                   /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_800269B4[];
extern M2C_UNK D_800814A0;

void func_8196ACE4(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    s16 temp_v0_4;
    s32 temp_lo;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 collide_x;
    u16 collide_y;
    s32 collide_z;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x8C));
    M2C_FIELD(arg0, s32 *, 0x8C) = (s32) (M2C_FIELD(arg0, s32 *, 0x8C) + M2C_FIELD(arg0, s32 *, 0x98));
    collide_x = M2C_FIELD(arg1, u16 *, 2);
    collide_y = M2C_FIELD(arg1, u16 *, 6);
    collide_z = M2C_FIELD(arg1, s16 *, 0xA);
    {
        u8 *page_8002 = (u8 *)&D_800269B4 - 0x69B4;
        M2C_FIELD(page_8002, s16 *, 0x69B4) = 1;
    }
    if ((func_800BCB04(collide_x, collide_y, collide_z) < 0x200) && ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0)) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x8C));
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s32 *, 0x98) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x90));
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg0, s32 *, 0x9C));
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) < 0x200) && ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0)) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x90));
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x94));
    {
        s32 temp_az = M2C_FIELD(arg0, s32 *, 0xA0);
        M2C_FIELD(arg0, s32 *, 0x94) += temp_az;
    }
    M2C_FIELD(arg0, s32 *, 0x8C) = (s32) ((M2C_FIELD(arg0, s32 *, 0x8C) * 0x60) / 100);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) ((M2C_FIELD(arg0, s32 *, 0x90) * 0x60) / 100);
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, volatile u16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0x94) = 0;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s16 *, 8) = 0;
        if (M2C_FIELD(arg0, s16 *, 0x2A) == 0) {
            M2C_FIELD(arg0, s16 *, 0x2A) = 1;
            M2C_FIELD(arg0, s32 *, 0x8C) = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
            M2C_FIELD(arg0, s32 *, 0x90) = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 2);
        }
    }
    temp_lo = (s32) (M2C_FIELD(arg0, s16 *, 0x2C) << 7) / (s16) M2C_FIELD(arg0, s16 *, 0x2E);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x34) + 1;
    M2C_FIELD(arg0, u16 *, 0x34) = temp_v0;
    if ((s16) temp_v0 == 3) {
        func_800478B8(arg2);
        M2C_FIELD(arg0, u16 *, 0x34) = 0U;
    }
    temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1C) + 0xC8;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    }
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) + 0xC8;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    }
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x2C) - 1;
    M2C_FIELD(arg0, s16 *, 0x2C) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        {
            u8 *page_8008 = (u8 *)0x80080000;
            M2C_FIELD(page_8008, s32 *, 0x14A0) |= 0x8000;
        }
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        {
            u8 *page_8008 = (u8 *)0x80080000;
            M2C_FIELD(page_8008, s32 *, 0x14A0) |= 0x8000;
        }
    }
}
