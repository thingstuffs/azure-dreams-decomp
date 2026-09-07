#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern u8 D_800DF334[];
extern int D_800814A8[4];
extern u16 D_80082E94;
extern u8 *D_800E3D7C[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
M2C_UNK func_80024330() __attribute__((noreturn));
M2C_UNK func_80024908();
M2C_UNK func_800A56E0();
M2C_UNK func_800B835C();
M2C_UNK func_800B8C20();
extern u8 D_80024980;
extern M2C_UNK D_80024998;
extern s16 D_800249A4;
extern s16 D_800249A6;

void func_8195281C(void *arg0, void *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 sp10[2];
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_v1;
    void *temp_a0;
    void *var_a1;
    u8 *temp_v1_2;
    void *temp_v1_3;
    u16 temp_v0_3;
    u16 temp_v1_4;
    void *temp_v1_5;
    u16 temp_v1_6;
    void *temp_v1_7;
    void **temp_a0_base;

    var_a1 = arg1;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0x16) = (u16) (M2C_FIELD(arg0, u16 *, 0x16) + 1);
    if ((u32) temp_v1 >= 5U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_80024008[(s32) temp_v1];
jt_c0:
    sp10[0] = 0x01000340;
    sp10[1] = 0x200020;
    func_800B835C(D_800DF334, sp10, 1, 0);
    sp10[0] = 0x01000360;
    func_800B835C(&D_80024980, sp10, 1, 0);
    M2C_FIELD(M2C_FIELD(D_800814A8, s32 *, 0), M2C_UNK **, 0xF4) = &D_80024998;
    func_800B8C20(M2C_FIELD(arg0, s32 *, 0) - 0x20, M2C_FIELD(arg0, u16 **, 4), 0, 0);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
jt_c1:
    temp_a0_base = (void **) D_800814A8;
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_27;
    }
    temp_v1_7 = *temp_a0_base;
    M2C_FIELD(arg0, s16 *, 0x18) = 0x12;
    M2C_FIELD(temp_v1_7, u16 *, 0xA6) = (u16) (M2C_FIELD(temp_v1_7, u16 *, 0xA6) - 1);
    M2C_FIELD(temp_v1_7, u8 *, 0xA8) = (u8) M2C_FIELD(arg0, u8 *, 8);
    temp_v1_3 = *temp_a0_base;
    M2C_FIELD(temp_v1_3, u8 *, 0xA9) = (u8) M2C_FIELD(arg0, u8 *, 9);
    temp_v1_3 = *temp_a0_base;
    D_800249A4 = 0;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xA);
    temp_v1_4 = M2C_FIELD(temp_v1_3, u16 *, 0x2A);
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_3 + 1;
    M2C_FIELD(arg0, u16 *, 0x14) = temp_v1_4;
    func_80024330();
    return;
jt_c2:
    if (M2C_FIELD(arg0, s16 *, 0x18) != 8) {
        goto block_8;
    }
    func_800A56E0(0x300);
block_8:
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x18) - 1;
    M2C_FIELD(arg0, s16 *, 0x18) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_28;
    }
    temp_v1_5 = M2C_FIELD(D_800814A8, void **, 0);
    M2C_FIELD(arg0, s16 *, 0x18) = 0x20;
    func_80024908(arg0 - 0x20, M2C_FIELD(arg0, s16 *, 0x14), M2C_FIELD(arg0, u8 *, 9), M2C_FIELD(temp_v1_5, void **, 0x60));
    M2C_FIELD(arg0, s16 *, 0xA) = (u16) M2C_FIELD(arg0, s16 *, 0xA) + 1;
    func_80024330();
    return;
jt_c3:
    temp_a0 = M2C_FIELD(M2C_FIELD(D_800814A8, s32 *, 0), void **, 0x60);
    if (temp_a0 == NULL) {
        goto block_18;
    }
    var_a1 = M2C_FIELD(temp_a0, void **, -0x14);
    M2C_FIELD(temp_a0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x1C) | 0x10000000);
    M2C_FIELD(var_a1, u8 *, 0xC) = (u8) (M2C_FIELD(var_a1, u8 *, 0xC) - 4);
    M2C_FIELD(var_a1, u8 *, 0xD) = (u8) (M2C_FIELD(var_a1, u8 *, 0xD) - 4);
    M2C_FIELD(var_a1, u8 *, 0xE) = (u8) (M2C_FIELD(var_a1, u8 *, 0xE) - 4);
    if ((u8) M2C_FIELD(var_a1, u8 *, 0xC) >= 0x20U) {
        goto block_14;
    }
    M2C_FIELD(var_a1, u8 *, 0xC) = 0x20U;
block_14:
    if ((u8) M2C_FIELD(var_a1, u8 *, 0xD) >= 0x20U) {
        goto block_16;
    }
    M2C_FIELD(var_a1, u8 *, 0xD) = 0x20U;
block_16:
    if ((u8) M2C_FIELD(var_a1, u8 *, 0xE) >= 0x20U) {
        goto block_18;
    }
    M2C_FIELD(var_a1, u8 *, 0xE) = 0x20U;
block_18:
    if (D_80082E94 & 0x8000) {
        goto block_21;
    }
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x18) - 1;
    M2C_FIELD(arg0, s16 *, 0x18) = temp_v0_2;
    if ((temp_v0_2 << 0x10) >= 0) {
        goto block_28;
    }
block_21:
    temp_a0 = M2C_FIELD(D_800E3D7C[0], void **, 0x60);
    if (temp_a0 == NULL) {
        goto block_23;
    }
    var_a1 = M2C_FIELD(temp_a0, void **, -0x14);
    M2C_FIELD(var_a1, s32 *, 0xC) = 0x808080;
block_23:
    temp_v1_6 = M2C_FIELD(arg0, u16 *, 0xA);
    D_800249A4 = 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v1_6 + 1;
    func_80024330();
    return;
jt_c4:
    if (D_800249A6 != 0) {
        goto block_28;
    }
    temp_v1_2 = (u8 *) D_80083460;
    M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0;
    M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_v1_2, u16 *, 0xA) - 1);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    M2C_FIELD(D_800814A0, s32 *, 0) = (s32) (M2C_FIELD(D_800814A0, s32 *, 0) | 0x8000);
block_27:
block_28:
    D_800249A6 = 0;
    return;
}
