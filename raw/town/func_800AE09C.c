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

M2C_UNK func_80064624();                /* extern */
M2C_UNK func_80064D20();                      /* extern */
M2C_UNK func_80064D50();                      /* extern */
M2C_UNK func_80064EC0();   /* extern */
M2C_UNK func_80064EE0();   /* extern */
M2C_UNK func_80064F00();            /* extern */
M2C_UNK func_80064F20();                     /* extern */
M2C_UNK func_800AB918();   /* extern */
extern M2C_UNK D_8006ADBC;
extern u8 D_80083160[];
extern u8 D_801C9E40[16];
extern u8 D_801DA714[];

void func_800AB7FC(void) {
    void *temp_s0;
    u8 *temp_s1;
    s32 temp_s2;
    register void *temp_call_a0 ASM_REG("$4");
    void *temp_global_a0;
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    s32 call_arg0;
    s32 call_arg1;
    s32 call_arg2;
    register u8 *tail_base ASM_REG("$2");

    temp_s1 = D_80083160;
    temp_s0 = temp_s1 + 0x18;
    temp_s2 = 0x200;
    M2C_FIELD(temp_s0, s32 *, 0x88) = temp_s2;
    func_80064F20(temp_s2);
    M2C_FIELD(temp_s0, s32 *, 0x78) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x7C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x80) = 0;
    func_80064EE0(0, 0, 0);
    M2C_FIELD(temp_s0, s16 *, 0x5A) = -0x100;
    M2C_FIELD(temp_s0, s16 *, 0x60) = -0x100;
    M2C_FIELD(temp_s0, s16 *, 0x66) = -0x100;
    M2C_FIELD(temp_s0, s16 *, 0x5C) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x62) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x68) = 0;
    func_80064D50(temp_s1 + 0x70);
    temp_call_a0 = temp_s1 + 0x50;
    ASM_KEEP(temp_call_a0);
    temp_v1 = -0x800;
    ASM_KEEP(temp_v1);
    temp_v0 = 0x800;
    ASM_KEEP(temp_v0);
    M2C_FIELD(temp_s0, s16 *, 0x38) = temp_v1;
    M2C_FIELD(temp_s0, s16 *, 0x3C) = temp_v1;
    temp_v1 = 0x800;
    ASM_KEEP(temp_v1);
    M2C_FIELD(temp_s0, s16 *, 0x3A) = temp_v0;
    temp_v0 = -0x800;
    ASM_KEEP(temp_v0);
    M2C_FIELD(temp_s0, s16 *, 0x3E) = temp_v1;
    M2C_FIELD(temp_s0, s16 *, 0x40) = temp_v0;
    M2C_FIELD(temp_s0, s16 *, 0x42) = temp_v1;
    M2C_FIELD(temp_s0, s16 *, 0x44) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x46) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x48) = 0;
    func_80064D20(temp_call_a0);
    M2C_FIELD(temp_s0, s32 *, 0x84) = 0x1000;
    func_80064624(0x1000, M2C_FIELD(temp_s0, s32 *, 0x88));
    temp_global_a0 = &D_8006ADBC;
    if ((M2C_FIELD(temp_global_a0, s16 *, 0x18) == 0xC) && (M2C_FIELD(temp_global_a0, s16 *, 0x1A) != 0x34)) {
        call_arg0 = 0xA0;
        call_arg1 = call_arg0;
        call_arg2 = call_arg0;
        M2C_FIELD(temp_s0, s16 *, 0x58) = temp_s2;
        M2C_FIELD(temp_s0, s16 *, 0x5E) = temp_s2;
        M2C_FIELD(temp_s0, s16 *, 0x64) = temp_s2;
    } else {
        call_arg0 = 0xB0;
        call_arg1 = call_arg0;
        call_arg2 = call_arg0;
        M2C_FIELD(temp_s0, s16 *, 0x58) = 0x3C0;
        M2C_FIELD(temp_s0, s16 *, 0x5E) = 0x3C0;
        M2C_FIELD(temp_s0, s16 *, 0x64) = 0x3C0;
    }
    func_80064EC0(call_arg0, call_arg1, call_arg2);
    func_80064F00(0xA0, 0x78);
    M2C_FIELD(temp_s1, s16 *, 0x18) = -0xBC;
    M2C_FIELD(temp_s1, s16 *, 0x1A) = -0x88;
    M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x172;
    M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x19A;
    M2C_FIELD(temp_s0, u8 *, 0x90) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0x91) = 0x80;
    M2C_FIELD(temp_s0, u8 *, 0x92) = 0x80;
    ASM_SCHED_BARRIER();
    tail_base = D_801C9E40;
    ASM_KEEP(tail_base);
    tail_base[0x19] = 0;
    tail_base[0x1A] = 0;
    tail_base[0x1B] = 0;
    ASM_SCHED_BARRIER();
    tail_base = D_801DA714;
    ASM_KEEP(tail_base);
    tail_base[0x19] = 0;
    tail_base[0x1A] = 0;
    tail_base[0x1B] = 0;
}
