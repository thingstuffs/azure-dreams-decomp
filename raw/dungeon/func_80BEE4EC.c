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
extern void *D_80170858[];
void func_8003DB94();
s32 func_8003E4FC();
void func_8003F540();
void *func_8003FC64();
void func_80041588();
int func_800445E0();
s32 func_8004491C();
s32 func_800498A0();
s32 func_80069EF8();
void func_8009A028();
void func_8009A3D0();
void func_800A18E8();
s32 func_800A504C();
s32 func_800A56E0();
s32 func_800ADC4C();
s32 func_800C77D0();
void func_80173904();
extern M2C_UNK D_8003E140;
extern s32 D_8006CD58;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_800DCEEC;
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8014A000;
extern M2C_UNK D_801736AC;
extern M2C_UNK D_80173B94;
extern M2C_UNK D_801742CC;
extern s32 D_801742D4[];
extern s16 D_801742E0;
extern M2C_UNK D_801742E4;
extern M2C_UNK D_801742E5;
extern s32 D_801742E8;

void func_80173CEC(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 var_s0;
    s16 var_s0_2;
    s32 temp_a0;
    register s32 temp_a3 ASM_REG("$7");
    register s32 temp_v0_3 ASM_REG("$2");
    register s32 var_v1 ASM_REG("$3");
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v1_2;
    s32 temp_v0_7;
    u8 temp_v1;
    register void *temp_a0_2 ASM_REG("$4");
    void *temp_a1;
    register void *temp_a1_2 ASM_REG("$5");
    register void *temp_a2 ASM_REG("$6");
    void *temp_s0;
    void *temp_s0_3;
    void *temp_v0_2;

    temp_s0_3 = &D_80083160;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 8U) {
        goto block_28;
    }
    (void)jt_keep; goto *D_80170858[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
jt_c1:
    func_80041588(&D_801742CC, &D_801742E4, 0);
    M2C_FIELD(arg0, s16 *, 0xA6) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg3, u16 *, 0x8A) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
jt_c2:
    temp_a0 = ((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7;
    if ((*(u8 *)&D_801742E4) == 0) {
        goto block_6;
    }
    if (temp_a0 == 2) {
        goto block_8;
    }
block_6:
    if (temp_a0 == 2) {
        goto block_28;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + 0x200);
    return;
block_8:
    func_80041588(&D_801742CC, &D_801742E4, 1);
    func_8003F540(0, D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    (*(s8 *)&D_801742E5) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_801742E5);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c3:
    temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x96);
    temp_v0 = temp_v1_2 - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_12;
    }
    temp_v0_7 = M2C_FIELD(&D_801742E5, u8 *, 0);
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v1_2;
    if (temp_v0_7 == 0) {
        goto block_28;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A56E0(0x300);
    return;
block_12:
    temp_a1 = M2C_FIELD(&D_800DCEEC, void **, func_800498A0(arg3) * 4);
    M2C_FIELD(temp_s0_3, u8 *, 0xA8) = (u8) (M2C_FIELD(temp_s0_3, u8 *, 0xA8) + ((s32) (M2C_FIELD(temp_a1, u8 *, 0) - M2C_FIELD(temp_s0_3, u8 *, 0xA8)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    M2C_FIELD(temp_s0_3, u8 *, 0xA9) = (u8) (M2C_FIELD(temp_s0_3, u8 *, 0xA9) + ((s32) (M2C_FIELD(temp_a1, u8 *, 1) - M2C_FIELD(temp_s0_3, u8 *, 0xA9)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    M2C_FIELD(temp_s0_3, u8 *, 0xAA) = (u8) (M2C_FIELD(temp_s0_3, u8 *, 0xAA) + ((s32) (M2C_FIELD(temp_a1, u8 *, 2) - M2C_FIELD(temp_s0_3, u8 *, 0xAA)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    return;
jt_c4:
    temp_v0_2 = func_8003FC64(0x12);
    if (temp_v0_2 == NULL) {
        goto block_28;
    }
    M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_80173B94;
    func_8004491C(temp_v0_2, &D_801736AC);
    temp_a3 = 0x808080;
    ASM_KEEP(temp_a3);
    M2C_FIELD(arg0, void **, 0xAC) = temp_v0_2;
    temp_a0_2 = arg3;
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    ASM_KEEP(temp_a0_2);
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    temp_a2 = M2C_FIELD(temp_v0_2, void **, 8);
    var_v1 = M2C_FIELD(arg1, s32 *, 8);
    temp_a1_2 = (void *) 0x80170000;
    M2C_FIELD(temp_a1_2, s16 *, 0x42E0) = -8;
    M2C_FIELD(temp_a2, s32 *, 8) = var_v1;
    temp_s0 = M2C_FIELD(temp_v0_2, void **, 0xC);
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s0, s32 *, 0xC) = temp_a3;
    temp_v0_3 = func_800498A0(temp_a0_2, temp_a1_2, temp_a2, temp_a3) - 1;
    var_v1 = temp_v0_3;
    ASM_KEEP(temp_v0_3);
    if ((temp_v0_3 << 0x10) >= 0) {
        goto block_16;
    }
    var_v1 = func_80069EF8() % 3;
block_16:
    func_8003DB94(temp_s0, D_801742D4[(s16) var_v1] + (s8 *) &D_8014A000, 0);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    var_s0 = 0;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
loop_17:
    func_80173904(arg0, arg1, arg2, arg3, func_80069EF8() & 0xFFF, 0);
    temp_v0_4 = var_s0 + 1;
    var_s0 = temp_v0_4;
    if (temp_v0_4 >= 8) {
        goto block_28;
    }
    goto loop_17;
jt_c5:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_5 + 1);
    if ((s16) temp_v0_5 >= 0x1E) {
        goto block_22;
    }
    var_s0_2 = 0;
loop_21:
    func_80173904(arg0, arg1, arg2, arg3, func_80069EF8() & 0xFFF, 0);
    temp_v0_6 = var_s0_2 + 1;
    var_s0_2 = temp_v0_6;
    if (temp_v0_6 < 8) {
        goto loop_21;
    }
block_22:
    temp_s0 = M2C_FIELD(arg0, void **, 0xAC);
    temp_s0 = M2C_FIELD(temp_s0, void **, 0xC);
    if (!(M2C_FIELD(temp_s0, u16 *, 0x14) & 0xE000)) {
        goto block_24;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c6:
block_24:
    if (M2C_FIELD(arg0, u8 *, 0x9B) != 6) {
        goto block_28;
    }
    if (func_800ADC4C(arg1, D_801742E8, D_801742E0, &D_800DCF5C) == 0) {
        goto block_28;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A18E8(M2C_FIELD(arg3, u8 *, 0x13), 3);
    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) | 0x80000000);
    return;
jt_c7:
    M2C_FIELD(arg3, s32 *, 0x60) = func_800A504C(arg2, arg3);
block_28:
    return;
}
