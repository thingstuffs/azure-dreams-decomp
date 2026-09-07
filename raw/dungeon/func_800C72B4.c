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

void *func_8003FE78();      /* extern */
s32 func_8009B390();                   /* extern */
M2C_UNK func_8009CE1C(); /* extern */
M2C_UNK func_800CC5F0(); /* extern */
M2C_UNK func_800CC88C();     /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_800CC370;
extern M2C_UNK D_800CC9BC;
extern void *D_800E3D7C;
extern u8 D_800E5908;
extern M2C_UNK D_8014A000;

void func_800CCA14(u16 arg0, u16 arg1, u16 arg2) {
    register s32 temp_a1 ASM_REG("$5");
    register s32 first_a3 ASM_REG("$7");
    register s32 temp_a3 ASM_REG("$7");
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0_3;
    s32 var_s4;
    u16 temp_x;
    u16 temp_y;
    u16 temp_z;
    u8 *count_base;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8003FE78(0, (D_800E5908 * 0xC8) + (u8 *)&D_8014A000, 0xA);
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800CC9BC;
    M2C_FIELD(temp_v0, u16 *, 0x20) = arg0;
    M2C_FIELD(temp_v0, u16 *, 0x22) = arg1;
    M2C_FIELD(temp_v0, u16 *, 0x24) = arg2;
    M2C_FIELD(temp_v0, s8 *, 0x27) = 8;
    count_base = (u8 *)&D_80083460;
    M2C_FIELD(count_base, u16 *, 0xA) = (u16) (M2C_FIELD(count_base, u16 *, 0xA) + 1);
    var_s4 = 3;
    do {
        temp_v0_2 = func_8003FE78(0, (((D_800E5908 * 5) + var_s4) * 0x28) + ((u8 *)&D_8014A000 + 0x28), 0xA);
        M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800CC370;
        temp_x = (u16) M2C_FIELD(temp_v0, u16 *, 0x20);
        ASM_SCHED_BARRIER();
        temp_a1 = var_s4 * 2;
        ASM_KEEP(temp_a1);
        M2C_FIELD(temp_v0_2, u16 *, 0x20) = temp_x;
        temp_y = (u16) M2C_FIELD(temp_v0, u16 *, 0x22);
        var_s4 -= 1;
        M2C_FIELD(temp_v0_2, u16 *, 0x22) = temp_y;
        temp_z = (u16) M2C_FIELD(temp_v0, u16 *, 0x24);
        M2C_FIELD(temp_v0_2, s8 *, 0x27) = 8;
        M2C_FIELD(temp_v0_2, s8 *, 0x26) = temp_a1;
        M2C_FIELD(temp_v0_2, u16 *, 0x24) = temp_z;
    } while (var_s4 >= 0);
    temp_s0 = (var_s4 << 0x1A) >> 0x10;
    first_a3 = temp_s0;
    ASM_KEEP(first_a3);
    var_s4 = 3;
    func_800CC88C((s16) M2C_FIELD(temp_v0, u16 *, 0x20), (s16) M2C_FIELD(temp_v0, u16 *, 0x22), (s16) M2C_FIELD(temp_v0, u16 *, 0x24), first_a3, 0);
    func_800CC88C((s16) M2C_FIELD(temp_v0, u16 *, 0x20), (s16) M2C_FIELD(temp_v0, u16 *, 0x22), (s16) M2C_FIELD(temp_v0, u16 *, 0x24), temp_s0, 1);
    do {
        ASM_KEEP(var_s4);
        temp_s0_2 = (var_s4 << 0x1A) >> 0x10;
        temp_a3 = temp_s0_2;
        ASM_KEEP(temp_a3);
        var_s4 -= 1;
        func_800CC5F0((s16) M2C_FIELD(temp_v0, u16 *, 0x20), (s16) M2C_FIELD(temp_v0, u16 *, 0x22), (s16) M2C_FIELD(temp_v0, u16 *, 0x24), temp_a3, 0, 0);
        func_800CC5F0((s16) M2C_FIELD(temp_v0, u16 *, 0x20), (s16) M2C_FIELD(temp_v0, u16 *, 0x22), (s16) M2C_FIELD(temp_v0, u16 *, 0x24), temp_s0_2, 1, 1);
    } while (var_s4 >= 0);
    temp_v0_3 = func_8009B390(M2C_FIELD(temp_v0, u16 *, 0x20), M2C_FIELD(temp_v0, u16 *, 0x22), (s16) M2C_FIELD(temp_v0, u16 *, 0x24));
    if (temp_v0_3 != 0) {
        func_8009CE1C(temp_v0_3, 0xC, M2C_FIELD(D_800E3D7C, u8 *, 0x11), 9, 0x400, 0, 3);
    }
}
/* MECHANISM: Byte-scaled table arithmetic and a held D_80083460 base fixed addressing/prologue.
   One-read x/y/z locals plus the a1 pin/barrier reproduced the first-loop load-delay schedule.
   One counter name, explicit signed shifts, and short-lived a3 pins closed both call seams. */
