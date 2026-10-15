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
s16 func_800BCB04();                   /* extern */
M2C_UNK func_800D2FC8();                    /* extern */
M2C_UNK func_800D3054();               /* extern */
M2C_UNK func_800D306C();               /* extern */
M2C_UNK func_800D30EC();                            /* extern */
M2C_UNK func_800D3120();                            /* extern */
extern u16 D_80083462;
extern M2C_UNK D_800E2284;

void func_800CD73C(void *arg0, void *arg1, void *arg2) {
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    s16 temp_a2;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1_2;
    u16 temp_a0_2;
    u16 temp_v1;

    if (D_80083462 & 0x2000) {
        func_800D3120();
        return;
    }
    temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2, arg0);
    }
    *((M2C_FIELD(arg0, u8 *, 0x9A) * 4) + &D_800E2284)(arg0, arg1, arg2, arg0);
    temp_v1 = M2C_FIELD(arg2, u16 *, 0x14);
    if (!(temp_v1 & 0x8000) && !(temp_v1 & 0x40)) {
        func_800478B8(arg2);
    }
    temp_a0 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_a1 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + temp_a0);
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a1);
    if (M2C_FIELD(arg0, u16 *, 0x98) & 8) {
        func_800D2FC8(temp_a0, temp_a1);
        return;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
    M2C_FIELD(arg0, s8 *, 0x9D) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
    if (!(M2C_FIELD(arg0, u16 *, 0x98) & 4)) {
        temp_v0_2 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20));
        if (temp_v0_2 < 0x200) {
            temp_a2 = (s16) M2C_FIELD(arg0, u16 *, 0x88);
            temp_a0_2 = M2C_FIELD(arg0, u16 *, 0x88);
            if ((M2C_FIELD(arg0, s16 *, 0x92) + temp_a2) < temp_v0_2) {
                func_800D306C(temp_a0_2, temp_v0_2, temp_a2);
                return;
            }
            if (temp_v0_2 >= temp_a2) {
                func_800D3054(temp_a0_2, temp_v0_2, temp_a2);
                return;
            }
            M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v0_2 - temp_a0_2);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x1C);
            if (temp_v1_2 & 0x40000000) {
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v1_2 & 0xBFFFFFFF);
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg0, u16 *, 0x88) - func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20))));
                func_800D30EC();
                return;
            }
            /* Duplicate return node #23. Try simplifying control flow for better match */
            M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x200);
            return;
        }
    }
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x200);
}
