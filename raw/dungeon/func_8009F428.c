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

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089008[];
void func_8003DB94();     /* extern */
M2C_UNK func_8003E188();            /* extern */
void func_80041E70();                      /* extern */
M2C_UNK func_80096088();              /* extern */
void func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800ACB98(); /* extern */
M2C_UNK func_800D8590();                      /* extern */
extern M2C_UNK D_80082E80;
extern s32 D_80083110[];
extern s16 D_80083228;
extern u8 D_800DD274[];

void func_800A4B88(void *arg0, s32 arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26 };
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK var_a2_3;
    M2C_UNK var_a2_4;
    s32 temp_a1;
    s32 *var_v0;
    s32 temp_v0;
    s32 var_v1;
    M2C_UNK *temp_a0;
    u8 var_a0;
    u8 var_a1;
    void *temp_s0;

    temp_a1 = (s16) (arg1 - 1);
    if ((u32) temp_a1 >= 0x1BU) {
        goto block_26;
    }
    (void)jt_keep; goto *D_80089008[(u32)(temp_a1)];
jt_c0:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x200);
    goto block_26;
jt_c1:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x400);
    goto block_26;
jt_c2:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) ((M2C_FIELD(arg0, s32 *, 0x1C) & 0xFFFDFFFF) | 0x10);
    goto block_26;
jt_c3:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x20);
    goto block_26;
jt_c4:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x40);
    goto block_26;
jt_c5:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x80);
    goto block_26;
jt_c7:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x800);
    goto block_26;
jt_c8:
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x1000);
    goto block_26;
jt_c26:
    temp_s0 = M2C_FIELD(arg0, void **, -0x14);
    var_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    var_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    var_a2 = 0x3000;
    if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x2000)) {
        goto block_12;
    }
    var_a2 = 0x300;
block_12:
    func_8009A3D0(var_a0, var_a1, var_a2);
    goto block_26;
jt_c10:
    temp_s0 = M2C_FIELD(arg0, void **, -0x14);
    var_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    var_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    var_a2_2 = 0x3000;
    if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x2000)) {
        goto block_15;
    }
    var_a2_2 = 0x300;
block_15:
    func_8009A3D0(var_a0, var_a1, var_a2_2);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x1C) | 0x2000;
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v0;
    var_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    var_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    var_a2_3 = 0x3000;
    if (!(temp_v0 & 0x2000)) {
        goto block_20;
    }
    var_a2_3 = 0x300;
    goto block_20;
jt_c11:
    temp_s0 = M2C_FIELD(arg0, void **, -0x14);
    var_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    var_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    var_a2_4 = 0x3000;
    if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x2000)) {
        goto block_19;
    }
    var_a2_4 = 0x300;
block_19:
    func_8009A3D0(var_a0, var_a1, var_a2_4);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & ~0x2000);
    var_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    var_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    do {
        var_a2_3 = 0x3000;
    } while (0);
block_20:
    func_8009A21C(var_a0, var_a1, var_a2_3);
    goto block_26;
jt_c9:
    func_8003E188(0x2E, 0);
    if (!(M2C_FIELD(arg0, s32 *, 0x14) & 0x20000000)) {
        goto block_23;
    }
    func_800ACB98(arg0, M2C_FIELD(arg0, s32 *, -0x18), M2C_FIELD(arg0, void **, -0x14), arg0);
    return;
block_23:
    func_800D8590(arg0);
    if (M2C_FIELD(arg0, u8 *, 0x13) != 0) {
        goto block_26;
    }
    func_80096088(arg0, arg0);
    temp_a0 = &D_80082E80;
    M2C_FIELD(temp_a0, M2C_UNK **, 0x2C) = D_800DD274;
    func_8003DB94(temp_a0, *(s32 *)(D_800DD274 + ((((s32) (D_80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 7) & 0x1C))), 0);
    var_v1 = 3;
    var_v0 = D_80083110;
    var_v0 += 3;
loop_25:
    *var_v0 = 0;
    var_v1 -= 1;
    var_v0 -= 1;
    if (var_v1 >= 0) {
        goto loop_25;
    }
jt_c6:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
jt_c16:
jt_c17:
jt_c18:
jt_c19:
jt_c20:
jt_c21:
jt_c22:
jt_c23:
jt_c24:
jt_c25:
block_26:
    func_80041E70(arg0);
    return;
}
