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

M2C_UNK func_8006390C();                            /* extern */
M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800672D8();                  /* extern */
M2C_UNK func_80176DA4();               /* extern */
M2C_UNK func_80176E7C();                            /* extern */
M2C_UNK func_801778C0();            /* extern */
extern M2C_UNK D_80086D8C;
extern s32 D_801781D8;
extern s32 D_801781DC;
extern s32 D_801781E0;
extern void *D_80189390;

void func_800404A8(void) {
    u16 sp10;
    u16 sp12;
    M2C_UNK sp14;
    s32 temp_a0_2;
    s32 temp_v0_2;
    u16 temp_v1;
    u32 temp_lo;
    void **var_v0;
    void *temp_a0;
    void *temp_v0;

    if (D_801781E0 & 1) {
        var_v0 = (void **)0x80190000;
        if (M2C_FIELD(&D_80086D8C, s32 *, 0) != 0) {
            func_8006390C();
            M2C_FIELD(&D_80086D8C, s32 *, 0x6D8C) = 0;
            goto block_3;
        }
    } else {
block_3:
        var_v0 = &D_80189390;
    }
    temp_a0 = *var_v0;
    sp10 = M2C_UNALIGNED32(M2C_FIELD(temp_a0, M2C_UNK *, 0x28));
    sp14 = M2C_UNALIGNED32(M2C_FIELD(temp_a0, M2C_UNK *, 0x2C));
    if (D_801781E0 & 1) {
        temp_a0_2 = D_801781D8 / 3;
        sp10 += temp_a0_2 * 3;
        func_80176DA4(temp_a0_2, D_801781DC / 3, D_801781DC / 3);
        return;
    }
    sp10 += (u16) D_801781D8;
    sp12 += (u16) D_801781DC;
    func_800672D8(&sp10, M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x10));
    func_80067014(0);
    temp_v1 = M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x28) + M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x2C);
    M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x28) = temp_v1;
    temp_v0 = M2C_FIELD(&D_80189390, void **, -0x6C70) + (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) * 8);
    if ((s16) temp_v1 < (M2C_FIELD(temp_v0, s16 *, 0x14) + M2C_FIELD(temp_v0, s16 *, 0x18))) {
        temp_lo = (s16) M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x2C) * M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x2E);
        func_801778C0(M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x10), (s32) (temp_lo + (temp_lo >> 0x1F)) >> 1, M2C_FIELD(&D_80189390, void **, -0x6C70));
        func_80176E7C();
        return;
    }
    M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x30) = 1;
    temp_v0_2 = M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) == 0;
    M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) = temp_v0_2;
    M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x28) = (u16) M2C_FIELD((M2C_FIELD(&D_80189390, void **, -0x6C70) + (temp_v0_2 * 8)), u16 *, 0x14);
    M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x2A) = (u16) M2C_FIELD((M2C_FIELD(&D_80189390, void **, -0x6C70) + (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) * 8)), u16 *, 0x16);
}
