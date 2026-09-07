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
extern s32 D_800E296C[3];
extern u8 D_800E2438[];
extern s16 D_80083228[5];
extern u8 D_80170A84[];
extern s32 D_80045C34[3];
extern u8 D_800E2440[];
extern u8 D_800E2448[];
extern u8 D_800E23E0[];
extern u8 D_800E2488[];
extern u8 D_80171A80[];
extern s32 D_8008346C[];
extern void *D_801708A0[];
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();               /* extern */
M2C_UNK func_8009D8A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_801708B8();      /* extern */
M2C_UNK func_80174C64(); /* extern */

void func_8017558C(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    s16 temp_a1;
    s16 temp_v1_4;
    s16 temp_s0;
    s32 *temp_a0;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u8 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_5;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1_2;

    s32 temp_flag;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 6) {
        goto block_46;
    }
    (void)jt_keep; goto *D_801708A0[(u32)(temp_v1)];
jt_c0:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_5;
    }
    {
        register s32 five ASM_REG("$5");
        func_8009D8A4();
        five = 5;
        ASM_KEEP(five);
        temp_flag = D_800E296C[0];
        M2C_FIELD(arg0, u16 *, 0x96) = five;
        D_800E296C[0] = temp_flag | 0x800000;
        M2C_FIELD(arg0, u8 *, 0x9B) = five;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
    goto block_46;
block_5:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    temp_a1 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
    temp_v1_4 = M2C_FIELD(arg3, u16 *, 0x88);
    temp_a1 -= temp_v1_4;
    if (M2C_FIELD(arg0, s16 *, 0x92) >= temp_a1) {
        goto block_7;
    }
    M2C_FIELD(arg0, u16 *, 0x92) = M2C_FIELD(arg0, u16 *, 0x92) + 0xC;
    if (temp_a1 >= (s16) M2C_FIELD(arg0, u16 *, 0x92)) {
        goto block_8;
    }
block_7:
    M2C_FIELD(arg0, u16 *, 0x92) = (u16) temp_a1;
block_8:
    if (M2C_FIELD(arg0, s16 *, 0x92) != 0) {
        goto block_10;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800E2438;
    func_80047784(arg2, D_800E2438[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
    M2C_FIELD(arg0, u16 *, 0x96) = 2U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg2, s16 *, 6) = 6;
    M2C_FIELD(arg0, u16 *, 0xA6) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
block_10:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((s16) temp_v0_2 != 1) {
        goto block_46;
    }
    temp_v0_3 = func_8003FD64(0x12, arg0 - 0x20);
    if (temp_v0_3 == NULL) {
        goto block_46;
    }
    M2C_FIELD(arg0, void **, 0xAC) = temp_v0_3;
    M2C_FIELD(temp_v0_3, u8 **, 0x10) = D_80170A84;
    func_8004491C(temp_v0_3, D_80045C34);
    temp_v0_4 = temp_v0_3 + 0x20;
    M2C_FIELD(temp_v0_4, s16 *, 0x38) = 5;
    M2C_FIELD(temp_v0_4, void **, 0x40) = arg0;
    M2C_FIELD(temp_v0_4, void **, 0x44) = arg1;
    temp_a0 = M2C_FIELD(temp_v0_3, s32 **, 0xC);
    M2C_FIELD(temp_a0, s16 *, 0x10) = 0x40;
    M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
    temp_v1_2 = M2C_FIELD(temp_v0_3, void **, 8);
    M2C_FIELD(temp_v1_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_v1_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) M2C_FIELD(arg3, u16 *, 0x88);
    temp_a0 = M2C_FIELD(temp_v0_3, s32 **, 0xC);
    M2C_FIELD(temp_a0, s16 *, 0x1E) = 0xA00;
    M2C_FIELD(temp_a0, s16 *, 0x1C) = 0xA00;
    M2C_FIELD(temp_a0, s8 *, 0xE) = 0;
    M2C_FIELD(temp_a0, s8 *, 0xD) = 0;
    M2C_FIELD(temp_a0, s8 *, 0xC) = 0;
    M2C_FIELD(temp_a0, u8 **, 8) = D_800E2488;
    goto block_46;
jt_c1:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        goto block_16;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_46;
    }
block_16:
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800E2440;
    func_80047784(arg2, D_800E2440[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x96) = 3U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg0, u16 *, 0xB6) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0xB8) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0xBA) = (u16) M2C_FIELD(arg3, u16 *, 0x88);
    goto block_46;
jt_c2:
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto block_46;
    }
    temp_v1_5 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = 0x1EU;
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, s8 *, 0xB2) = 0;
    M2C_FIELD(arg0, s8 *, 0xB4) = 0;
    M2C_FIELD(arg0, s8 *, 0xB3) = 0;
    temp_v1_5 += 1;
    M2C_FIELD(arg0, u8 *, 0x9B) = temp_v1_5;
    goto block_46;
jt_c3:
    func_80174C64(arg0, arg1, arg2, arg3);
    goto block_46;
jt_c4:
    temp_v1_3 = M2C_FIELD(arg0, u8 *, 0xB1);
    if (temp_v1_3 == 1) {
        goto block_36;
    }
    if ((s32) temp_v1_3 >= 2) {
        goto block_28;
    }
    if (temp_v1_3 == 0) {
        goto block_31;
    }
    goto block_46;
block_28:
    if (temp_v1_3 == 2) {
        goto block_39;
    }
    goto block_46;
block_31:
    temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_7;
    if ((s16) temp_v0_7 != 1) {
        goto block_33;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0xB6);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 0xB8);
    M2C_FIELD(arg3, u16 *, 0x88) = (u16) M2C_FIELD(arg0, u16 *, 0xBA);
    temp_v0_8 = M2C_FIELD(arg0, u16 *, 0xA6);
    M2C_FIELD(arg3, s16 *, 0x2A) = (s16) temp_v0_8;
    temp_s0 = ((s32) (*D_80083228 + (s16) temp_v0_8 + 0x100) >> 9) & 7;
    func_80047738(arg2, M2C_FIELD(arg2, u8 **, 0x2C)[temp_s0], M2C_FIELD(arg2, s8 *, 4));
    M2C_FIELD(arg0, s16 *, 0x94) = temp_s0;
block_33:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 0x10) {
        goto block_46;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB1) = (u8) (M2C_FIELD(arg0, u8 *, 0xB1) + 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0x9F7F);
    goto block_46;
block_36:
    temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_9 + 1);
    if ((s16) temp_v0_9 < 4) {
        goto block_46;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB1) = (u8) (M2C_FIELD(arg0, u8 *, 0xB1) + 1);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800E2448;
    func_80047784(arg2, D_800E2448[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0x9F7F);
    func_800A56E0(0x801);
    goto block_46;
block_39:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_46;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    if (M2C_FIELD(arg2, u8 **, 0x2C) == D_800E23E0) {
        goto block_46;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800E23E0;
    func_80047784(arg2, D_800E23E0[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x96) = 5U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    if (M2C_FIELD(arg0, u8 *, 0xB0) != 0) {
        goto block_46;
    }
    func_801708B8(arg0, arg1, arg2);
    goto block_46;
jt_c5:
    temp_v0_10 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_10 - 1);
    if ((temp_v0_10 << 0x10) > 0) {
        goto block_46;
    }
    M2C_FIELD(arg2, s16 *, 6) = 0;
    func_800AD594(arg3, 0x1000);
    M2C_FIELD(arg0, u8 **, 0x8C) = D_80171A80;
    *D_8008346C = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
block_46:
    return;
}
