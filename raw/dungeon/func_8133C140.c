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

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
void func_800A9C18(void *, void *, void *, s32); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80171D74;
extern M2C_UNK D_80173DA4;
extern void *D_80175D54;

void func_80173140(void) {
    register s32 temp_v1 ASM_REG("$3");
    register s32 flag_mask ASM_REG("$3");
    register s32 temp_v0_2 ASM_REG("$2");
    register s16 temp_neg ASM_REG("$2");
    register s32 call2_a0 ASM_REG("$4");
    register s32 call2_a1 ASM_REG("$5");
    register void *temp_v0 ASM_REG("$18");
    M2C_UNK var_a2;
    s32 env_first;
    s32 env_second;
    void *temp_a1;
    void *temp_s0;
    void *temp_s1;
    u8 *temp_v1_global;

    temp_v0 = func_8003FD64(0x112, &D_80083498);
    ASM_KEEP(temp_v0);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80171D74;
        M2C_FIELD(temp_s1, s8 *, 0x13) = 2;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1_global = (u8 *)&D_80082E80;
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(&D_80083498, void **, 8), u16 *, 0xA);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        env_first = temp_v1_global[0x24];
        M2C_FIELD(temp_s0, u8 *, 0x24) = (u8) (env_first - 1);
        env_second = temp_v1_global[0x25];
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_80173DA4;
        M2C_FIELD(temp_s0, u8 *, 0x25) = (u8) (env_second + 7);
        func_800A9C18(temp_v0, temp_a1, temp_s0, 0);
        M2C_FIELD(temp_s1, s16 *, 0x2A) = 0xC00;
        func_80047784(temp_s0, ((u8 *) M2C_FIELD(temp_s0, void **, 0x2C))[((s32) (D_80083228 + 0xD00) >> 9) & 7], 0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        temp_v0_2 = M2C_FIELD(temp_s1, s32 *, 0x1C);
        ASM_KEEP(temp_v0_2);
        flag_mask = 0x40000;
        ASM_KEEP(flag_mask);
        M2C_FIELD(temp_s1, s32 *, 0xA0) = 0;
        ASM_MEM_BARRIER();
        temp_v0_2 |= flag_mask;
        M2C_FIELD(temp_s1, s32 *, 0x1C) = temp_v0_2;
        ASM_KEEP(temp_v0_2);
        temp_v1 = temp_v0_2;
        ASM_KEEP(temp_v1);
        temp_neg = -0x20;
        ASM_KEEP(temp_neg);
        temp_v1 &= 0x2000;
        ASM_KEEP(temp_v1);
        M2C_FIELD(temp_s1, s16 *, 0x92) = temp_neg;
        call2_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
        call2_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
        ASM_KEEP(call2_a0);
        ASM_KEEP(call2_a1);
        var_a2 = 0x3000;
        if (temp_v1) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call2_a0, call2_a1, var_a2);
        func_8009A028(temp_s1);
        D_80175D54 = temp_v0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (M2C_UNK *) ((s32) M2C_FIELD(temp_v0, M2C_UNK **, 0x10) | 0x80000000);
    }
}

/* MECHANISM: The 0x20 frame holds s2=obj, s1=obj+0x20, and s0 as the reused global/object base.
   A held D_80082E80 byte base plus split env_first/env_second live ranges fixes the call schedule.
   Byte indexing, split v0/v1 flag RMW roles, and a store/OR memory seam close the final rotation. */
