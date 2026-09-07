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

void func_800199A8(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_8003E4FC();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8003F5E0();                         /* extern */
M2C_UNK func_80053DA8();                    /* extern */
s16 func_8005405C();                             /* extern */
M2C_UNK func_800542BC();                            /* extern */
M2C_UNK func_8005FE18();                     /* extern */
M2C_UNK func_80067014();                     /* extern */
extern M2C_UNK D_8006E61C;
extern M2C_UNK D_80080AF0;
extern s32 D_80081480;
extern M2C_UNK D_8008148C;

s32 func_80019894(s16 arg0) {
    s16 temp_v0;
    s32 temp_a1;
    u8 *temp_s0;
    void *temp_s1;
    void *temp_arg8;

    temp_s1 = (arg0 * 0xC) + (s8 *)&D_8006E61C;
    temp_v0 = M2C_FIELD(temp_s1, u16 *, 0) - 1;
    temp_s0 = temp_v0 + (u8 *)&D_80080AF0;
    temp_a1 = arg0 + 1;
    if (*temp_s0 == temp_a1) {
        s32 zero = 0;

        ASM_TAILSLOT_PIN(zero);
        func_800199A8();
        return 0;
    }
    func_80053DA8(0x72, temp_a1);
    func_800542BC();
    *temp_s0 = arg0 + 1;
    func_80067014(0);
    func_8005FE18(0);
    temp_arg8 = M2C_FIELD(temp_s1, void **, 8);
    D_80081480 = M2C_FIELD(&D_8008148C, s32 *, 0);
    func_8003E4FC(6, temp_arg8, 0);
    func_8003E4FC(6, M2C_FIELD(temp_s1, s32 *, 4), 0);
    func_8003F320();
    func_8003F5E0(D_8008148C);
    func_80053DA8(((2 << temp_v0) | 0x10) & 0xFFFF);
    func_800542BC();
    do {

    } while (func_8005405C((s16) M2C_FIELD(temp_s1, u16 *, 0)) != 1);
    return 1;
}

/* MECHANISM: Byte-addressed bases preserve the 12-byte record and byte counter indexing,
   while their lifetimes naturally produce the retail 0x28 frame and s1/s3/s2/s0 saves.
   A named field8 argument exposes the global-copy jal slot; the zero-arg noreturn contract
   plus guarded v0 tail-slot pin produces the retail j with move-zero delay. */
