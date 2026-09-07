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

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_80025160;
extern M2C_UNK D_80025340;
extern u16 D_8002632A;
extern u8 D_80026478[];
extern s16 D_80026878;

void *func_8002569C(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s16 temp_v0_2;
    u16 temp_a3;
    u16 temp_a1;
    u16 temp_a1_2;
    u16 temp_v1_2;
    void *temp_a0;
    u8 *temp_base;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v1;

    temp_v0 = func_8003FD64(0x202, arg4);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80025160;
        func_8004491C(temp_v0, &D_80025340);
        temp_s2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s2, s16 *, 2) = (s16) (M2C_FIELD(arg0, u16 *, 2) + ((s32) (func_80064584(arg1) * arg2) >> 0xF));
        M2C_FIELD(temp_s2, s16 *, 6) = (s16) (M2C_FIELD(arg0, u16 *, 6) + ((s32) (func_800644B8(arg1) * arg2) >> 0xF));
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA) + ((s32) (arg3 << 0x10) >> 0x13);
        M2C_FIELD(temp_s2, s16 *, 0xA) = temp_v0_2;
        if (D_80026878 < temp_v0_2) {
            M2C_FIELD(temp_s2, s16 *, 0xA) = D_80026878;
        }
        M2C_FIELD(temp_s2, u16 *, 0xE) = (u16) M2C_FIELD(arg0, u16 *, 2);
        M2C_FIELD(temp_s2, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 6);
        M2C_FIELD(temp_s2, u16 *, 0x16) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
        temp_v1 = (void *) 0xE04020;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s32 *, 0xC) = (s32) temp_v1;
        temp_a3 = D_8002632A;
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x16) = arg1;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = arg3;
        M2C_FIELD(temp_v1, s16 *, 0x18) = arg2;
        ASM_KEEP_NV(temp_v1);
        M2C_FIELD(temp_v1, u16 *, 0x22) = temp_a3;
        if ((s16) temp_a3 < 0x71) {
            temp_base = D_80026478;
            temp_a0 = &temp_base[(s16) temp_a3 * 8];
            temp_a1 = M2C_FIELD(temp_s2, u16 *, 0xE);
            temp_v0_3 = &temp_base[((s16) temp_a3 + 0x10) * 8];
            M2C_FIELD(temp_a0, u16 *, 0) = temp_a1;
            M2C_FIELD(temp_v0_3, u16 *, 0) = temp_a1;
            temp_v1_2 = M2C_FIELD(temp_s2, u16 *, 0x12);
            M2C_FIELD(temp_a0, u16 *, 2) = temp_v1_2;
            M2C_FIELD(temp_v0_3, u16 *, 2) = temp_v1_2;
            temp_a1_2 = M2C_FIELD(temp_s2, u16 *, 0x16);
            D_8002632A = temp_a3 + 1;
            M2C_FIELD(temp_a0, u16 *, 4) = temp_a1_2;
            M2C_FIELD(temp_v0_3, u16 *, 4) = temp_a1_2;
        }
    }
    return temp_v0;
}
/* MECHANISM: Natural long-lived arguments/results reproduce the 0x38 frame and nine-register save set.
   Direct scalar globals plus one cached counter remove remats; byte indexing with a held table base fixes scaling.
   One guarded v1 lifetime carries 0xE04020, then object+0x20, keeping the count store branch-slot eligible.
   Relocating ASM_KEEP_NV after the three field stores selects retail's final lhu/addiu ready-list order. */
