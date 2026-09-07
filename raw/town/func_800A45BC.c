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

M2C_UNK func_800649A0();                            /* extern */
M2C_UNK func_80064A40();                            /* extern */
M2C_UNK func_80064CF0();                      /* extern */
M2C_UNK func_80064D80();                      /* extern */
M2C_UNK func_80065320();     /* extern */
M2C_UNK func_800A1DD4();                            /* extern */
M2C_UNK func_800A1E14();                            /* extern */
M2C_UNK func_800A1E54();                            /* extern */
M2C_UNK func_800A1EDC();                            /* extern */
extern s32 D_800814A0;

void func_800A1D1C(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *global_page;
    register void *arg2_local ASM_REG("$18");
    register u8 *scratch ASM_REG("$19");
    void *temp_a0;
    void *temp_s0_2;
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x10);
    arg2_local = arg2;
    scratch = (u8 *)0x1F800000;
    if (M2C_FIELD(temp_s1, s16 *, 0xA) != 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        global_page = (u8 *)0x80080000;
        ASM_KEEP(global_page);
        M2C_FIELD(global_page, s32 *, 0x14A0) |= 0x8000;
        func_800A1EDC();
        return;
    }
    ASM_KEEP(arg2_local);
    ASM_KEEP(scratch);
    M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *), 0)(arg0, arg1, arg2_local);
    if (M2C_FIELD(arg0, u8 *, 0x3C) != 0) {
        M2C_FIELD(arg2_local, u8 *, 0xC) = M2C_FIELD(temp_s1, u8 *, 0x10);
        func_800A1DD4();
        return;
    }
    var_v0 = M2C_FIELD(temp_s1, s16 *, 0x10) * 3;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    M2C_FIELD(arg2_local, s8 *, 0xC) = (s8) (var_v0 >> 2);
    if (M2C_FIELD(arg0, u8 *, 0x3D) != 0) {
        M2C_FIELD(arg2_local, u8 *, 0xD) = M2C_FIELD(temp_s1, u8 *, 0x10);
        func_800A1E14();
        return;
    }
    var_v0_2 = M2C_FIELD(temp_s1, s16 *, 0x10) * 3;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    M2C_FIELD(arg2_local, s8 *, 0xD) = (s8) (var_v0_2 >> 2);
    if (M2C_FIELD(arg0, u8 *, 0x3E) != 0) {
        M2C_FIELD(arg2_local, u8 *, 0xE) = M2C_FIELD(temp_s1, u8 *, 0x10);
        func_800A1E54();
        return;
    }
    var_v0_3 = M2C_FIELD(temp_s1, s16 *, 0x10) * 3;
    if (var_v0_3 < 0) {
        var_v0_3 += 3;
    }
    M2C_FIELD(arg2_local, s8 *, 0xE) = (s8) (var_v0_3 >> 2);
    M2C_FIELD(scratch, u16 *, 0x2C) = M2C_FIELD(arg0, u16 *, 0x24);
    M2C_FIELD(scratch, u16 *, 0x2E) = M2C_FIELD(arg0, u16 *, 0x28);
    M2C_FIELD(scratch, u16 *, 0x30) = M2C_FIELD(arg0, u16 *, 0x2C);
    temp_s0 = M2C_FIELD(arg0, s16 *, 0x22) != 0;
    func_800649A0();
    temp_s0_2 = temp_s1 + ((temp_s0 << 5) + 0x14);
    func_80064CF0(temp_s0_2);
    func_80064D80(temp_s0_2);
    temp_a0 = scratch + 0x2C;
    func_80065320(temp_a0, temp_a0, (void *)((u32)scratch | 0x98));
    func_80064A40();
    M2C_FIELD(arg1, u16 *, 2) = M2C_FIELD(scratch, u16 *, 0x2C);
    M2C_FIELD(arg1, u16 *, 6) = M2C_FIELD(scratch, u16 *, 0x2E);
    M2C_FIELD(arg1, u16 *, 0xA) = M2C_FIELD(scratch, u16 *, 0x30);
}
/* MECHANISM: Pinned s3 scratch and s2 arg2 holds produce the five-register 0x28 frame.
   A held 0x80080000 page base recovers the v1 RMW; signed halfword loads and tail-arm byte copies recover the body.
   Assigning scratch before the branch but fencing both holds at fallthrough fills retail's load and branch delay slots. */
