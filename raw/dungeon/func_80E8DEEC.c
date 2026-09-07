#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A56E0();
extern M2C_UNK func_800AD058();
extern M2C_UNK func_80174D48();
extern s16 D_8008346A[];

void func_801736EC(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK one;
    register M2C_UNK color ASM_REG("$5");
    M2C_UNK temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    one = 1;
    if (temp_v1 == one) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto block_ge_2;
    }
    if (temp_v1 == 0) {
        goto block_8;
    }
    goto block_end;

block_ge_2:
    if (temp_v1 == 2) {
        goto block_20;
    }
    goto block_end;

block_8:
    if (D_8008346A[0] != 0) {
        goto block_end;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8)one;

block_10:
    if (M2C_FIELD(arg3, u8 *, 0x49) != 0) {
        func_80174D48(arg1, arg2, arg3);
        M2C_FIELD(arg3, s8 *, 0x48) = 0;
        M2C_FIELD(arg3, u8 *, 0x49) = 0U;
    }
    color = 0x808080;
    ASM_KEEP(color);
    M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
    M2C_FIELD(arg2, u16 *, 0x12) = (u16)(M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
    M2C_FIELD(arg3, s32 *, 0x1C) = M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000;
    M2C_FIELD(arg2, s32 *, 0xC) = color;
    M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8)(M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A56E0(0x805, color);
    goto block_end;

block_20:
    func_800AD058(arg0, arg1, arg2, arg3);

block_end:
    return;
}
