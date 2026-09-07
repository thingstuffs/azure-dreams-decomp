#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Copy4;
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

M2C_UNK func_8003830C();                  /* extern */
M2C_UNK func_80051520();      /* extern */
M2C_UNK func_80051804();         /* extern */
M2C_UNK func_8005184C();         /* extern */
M2C_UNK func_80051898();                  /* extern */
M2C_UNK func_80051900();                       /* extern */
M2C_UNK func_80051B50(); /* extern */
M2C_UNK func_8007BF50();                /* extern */
M2C_UNK func_8007BF80();                  /* extern */
extern M2C_UNK D_8009DDE4[];
extern s16 D_80400660[];
extern s32 D_80400668[];
extern s16 D_804006AC[];
extern s16 D_804006BC[];
extern s16 D_804006C0[];
extern s32 D_80408CF4[];
extern s32 D_80408CFC[];
extern u8 D_8009DDD8[];
__asm__(".set D_8009DDD8, 0x8009DDD8");

/* The retail live range keeps the descriptor cursor in one saved register. */

void func_80404EA0(void *arg0) {
    s16 sp10[32];
    s16 sp50[8];
    s16 sp60[4];
    s16 var_a3_2;
    s32 *var_a2_2;
    s32 *var_a2_end;
    s32 var_a0;
    s32 descriptor_value;
    s32 bit_one;
    s16 height_b0;
    u32 hours;
    u32 mins;
    u32 mins_q;
    u32 secs;
    u32 secs_q;
    void *temp_s0;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s1;
    void *temp_s2;
    void *var_a1;
    void *final_sp;
    s32 *descriptor_base;

    temp_s2 = M2C_FIELD(arg0, void **, 0xB18);
    func_8003830C(M2C_FIELD(arg0, s32 *, 0x7C) + 1, sp10);
    func_8007BF50(sp10, D_80400660);
    func_8007BF50(sp10, (s16 *)((M2C_FIELD(arg0, s32 *, 0x7C) << 7) + (s32)&D_8009DDE4));
    temp_s0 = arg0 + 0x80;
    func_80051B50(temp_s0, sp10, 1);
    M2C_FIELD(temp_s2, void **, 0) = temp_s0;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0xA9;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x110;
    temp_s2 = M2C_FIELD(arg0, void **, 0xB1C);
    memcpy(sp10, D_80400668, 0x2A);
    func_80051B50(arg0 + 0x188, sp10, 1);
    M2C_FIELD(temp_s2, void **, 0) = arg0 + 0x188;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0xBC;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x110;
    if (M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), s32 *, 8) != 0) {
        temp_s2 = M2C_FIELD(arg0, void **, 0xB20);
        func_8007BF80(sp10, D_80408CF4[0]);
        func_8003830C(M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), s32 *, 0x34), sp50);
        func_8007BF50(sp10, sp50);
        func_8007BF50(sp10, D_804006AC);
        temp_s0_3 = arg0 + 0x290;
        func_80051B50(temp_s0_3, sp10, 1);
        M2C_FIELD(temp_s2, void **, 0) = temp_s0_3;
        M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0xBC;
        M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x140;
    }
    temp_s2 = M2C_FIELD(arg0, void **, 0xB24);
    func_80051804(M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), s32 *, 0x24), 0xA, sp10);
    func_80051900(sp10);
    temp_s0_4 = arg0 + 0x398;
    func_80051520(temp_s0_4, sp10, 1);
    M2C_FIELD(temp_s2, void **, 0) = temp_s0_4;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0x140;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x110;
    temp_s2 = M2C_FIELD(arg0, void **, 0xB28);
    func_80051898(M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), u32 *, 0x1C), sp10);
    hours = M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), u32 *, 0x1C) / 216000;
    func_80051804(hours, 3, sp10);
    func_8007BF50(sp10, D_804006BC);
    mins = M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), u32 *, 0x1C) / 3600;
    mins_q = mins / 3600;
    func_8005184C(mins - mins_q * 3600, 2, sp60);
    func_8007BF50(sp10, sp60);
    func_8007BF50(sp10, D_804006BC);
    secs = M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), u32 *, 0x1C) / 60;
    secs_q = secs / 60;
    func_8005184C(secs - secs_q * 60, 2, sp60);
    func_8007BF50(sp10, sp60);
    func_80051900(sp10);
    temp_s0_5 = arg0 + 0x4A0;
    func_80051520(temp_s0_5, sp10, 1);
    M2C_FIELD(temp_s2, void **, 0) = temp_s0_5;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0x147;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x120;
    temp_s2 = M2C_FIELD(arg0, void **, 0xB2C);
    func_80051804(M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), s32 *, 0x2C), 4, sp10);
    func_80051900(sp10);
    temp_s0_6 = arg0 + 0x5A8;
    func_80051520(temp_s0_6, sp10, 1);
    M2C_FIELD(temp_s2, void **, 0) = temp_s0_6;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0xF2;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x120;
    temp_s2 = M2C_FIELD(arg0, void **, 0xB30);
    memcpy(sp10, D_804006C0, 3);
    final_sp = sp10;
    func_80051900(final_sp);
    temp_s1 = arg0 + 0x6B0;
    func_80051520(temp_s1, final_sp, 1);
    var_a0 = 0;
    bit_one = 1;
    descriptor_base = D_80408CFC;
    var_a2_end = descriptor_base + 10;
    height_b0 = 0xB0;
    var_a3_2 = 0x38;
    var_a2_2 = descriptor_base;
    var_a1 = arg0;
    M2C_FIELD(temp_s2, void **, 0) = temp_s1;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = 0x180;
    M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = 0x130;
    do {
        temp_s2 = M2C_FIELD(var_a1, void **, 0xB34);
        if ((bit_one << var_a0) & M2C_FIELD(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7), s32 *, 0x30)) {
            descriptor_value = *var_a2_2;
        } else {
            descriptor_value = *var_a2_end;
        }
        var_a2_2 += 1;
        var_a1 += 4;
        M2C_FIELD(temp_s2, s32 *, 0) = descriptor_value;
        var_a0 += 1;
        M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 8) = var_a3_2;
        M2C_FIELD(M2C_FIELD(temp_s2, void **, 4), s16 *, 0xA) = height_b0;
        var_a3_2 += 0x10;
    } while (var_a0 < 0xA);
}
