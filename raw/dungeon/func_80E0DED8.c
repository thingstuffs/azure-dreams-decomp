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

M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_8009A66C(); /* extern */
s16 func_800A0818();             /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80176460[8];

void func_801716D8(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0_2;
    register s32 temp_a2 ASM_REG("$6");
    s32 temp_s1;
    s32 temp_s2;
    s32 next_x;
    s32 next_y;
    s32 next_flag;
    void *temp_v0;
    register void *state ASM_REG("$16") = arg3;

    if ((M2C_FIELD(state, s8 *, 0x71) > 0) && ((s32) (u8) M2C_FIELD(state, s8 *, 0x71) > M2C_FIELD(state, s16 *, 0x8A))) {
        if (M2C_FIELD(arg2, void **, 0x2C) != D_80176460) {
            M2C_FIELD(arg2, void **, 0x2C) = D_80176460;
            func_80047784(arg2, D_80176460[((D_80083228 + M2C_FIELD(state, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        temp_s1 = M2C_FIELD(arg2, u8 *, 0x24);
        temp_s2 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (M2C_FIELD(state, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(temp_s1, temp_s2, var_a2);
        temp_v0 = state + M2C_FIELD(state, s16 *, 0x8A);
        temp_v0_2 = func_800A0818(temp_s1, temp_s2, M2C_FIELD(temp_v0, u8 *, 0x74), M2C_FIELD(temp_v0, u8 *, 0x7C), arg0 + 0x98);
        func_8009A66C(temp_v0_2, arg2, state, 0x20);
        M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD((state + M2C_FIELD(state, s16 *, 0x8A)), u8 *, 0x74);
        M2C_FIELD(arg2, u8 *, 0x25) = (u8) M2C_FIELD((state + M2C_FIELD(state, s16 *, 0x8A)), u8 *, 0x7C);
        M2C_FIELD(state, s16 *, 0x8A) = (s16) ((u16) M2C_FIELD(state, s16 *, 0x8A) + 1);
        next_flag = M2C_FIELD(state, s32 *, 0x1C) & 0x2000;
        next_x = M2C_FIELD(arg2, u8 *, 0x24);
        next_y = M2C_FIELD(arg2, u8 *, 0x25);
        ASM_SCHED_BARRIER();
        var_a2_2 = 0x3000;
        if (next_flag) {
            var_a2_2 = 0x300;
        }
        func_8009A21C(next_x, next_y, var_a2_2);
        M2C_FIELD(state, s16 *, 0x2A) = temp_v0_2;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0xF;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(state, s32 *, 0x1C) = (s32) (M2C_FIELD(state, s32 *, 0x1C) | 0x40000000);
        if (D_80083462 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x96) = 8;
        temp_a2 = (u8) M2C_FIELD(state, s8 *, 0x71);
        if ((s32) temp_a2 > 0) {
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) (8 / (s32) temp_a2);
        }
        ASM_KEEP(temp_a2);
    }
    ASM_KEEP(state);
}

/* MECHANISM: A guarded $s0 state-base pin restores the retail 0x30 frame and
   saved-register roles; byte-table typing fixes the indexed lbu sequence.
   A cached flag plus schedule seam preserves the second-call order, while a
   widened $a2 divisor pin closes the lbu/blez/div tail live range. */
