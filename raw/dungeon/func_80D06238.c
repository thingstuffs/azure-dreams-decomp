#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
extern M2C_UNK D_80157E54;
extern M2C_UNK D_80157E5C;
extern M2C_UNK D_80157E64;

void func_80153A38(void *arg0, void *arg1, void *arg2) {
    u16 sp10;
    s32 temp_v1;
    void *temp_a0;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_s0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x20) - 0x20;
    if (!(M2C_FIELD(temp_a0, u16 *, 0x1E) & 0x8000)) {
        temp_s0 = M2C_FIELD(temp_a0, void **, 0xC);
        temp_a1 = M2C_FIELD(temp_a0, void **, 8);
        M2C_FIELD(arg2, s16 *, 6) = (s16) (M2C_FIELD(temp_s0, u16 *, 6) + 1);
        if (M2C_FIELD(temp_s0, s8 *, 4) == 0) {
            M2C_FIELD(arg2, s16 *, 0x1E) = 0x400;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0x400;
        }
        if (M2C_FIELD(temp_s0, s8 *, 4) == 1) {
            M2C_FIELD(arg2, s16 *, 0x1E) = 0x700;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0x700;
        }
        if (M2C_FIELD(temp_s0, s8 *, 4) == 2) {
            M2C_FIELD(arg2, s16 *, 0x1E) = 0xA00;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0xA00;
        }
        if (M2C_FIELD(temp_s0, s8 *, 4) == 3) {
            M2C_FIELD(arg2, s16 *, 0x1E) = 0x700;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0x700;
        }
        if (M2C_FIELD(temp_s0, s8 *, 4) == 4) {
            M2C_FIELD(arg2, s16 *, 0x1E) = 0x400;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0x400;
        }
        M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_a1, u16 *, 2);
        M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_a1, u16 *, 6);
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_a1, u16 *, 0xA);
        temp_a1_2 = M2C_FIELD(temp_a0, void **, 0xC);
        if (func_8003DE58(M2C_FIELD(temp_a1_2, s32 *, 8), temp_a1_2, &sp10, 0) != 0) {
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + sp10);
            M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + sp12);
            M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + sp14);
        }
        temp_v1 = M2C_FIELD(temp_s0, s32 *, 0x2C);
        if ((temp_v1 != &D_80157E54) && (temp_v1 != &D_80157E5C) && (temp_v1 != &D_80157E64)) {
            goto block_16;
        }
    } else {
block_16:
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
