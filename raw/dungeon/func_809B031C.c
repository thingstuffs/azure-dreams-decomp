#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_801699CC(void *, void *, void *);      /* extern */

void func_80169B1C(void *arg0, void *arg1, void *arg2) {
    s16 sp10;
    u16 sp12;
    u16 sp14;
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_a0_2;
    s32 temp_a0_4;
    u8 temp_a0_3;
    u8 temp_a0_5;
    void *temp_a0;
    void *temp_s0;

    sp10 = 0;
    sp12 = 0;
    sp14 = -(s32) *(u8 *)0x800DDC42 - 8;
    temp_a0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, -0x18);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_a0, u16 *, 2);
    M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(temp_a0, u16 *, 6) + sp12);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(temp_a0, u16 *, 0xA) + sp14);
    if (M2C_FIELD(arg0, s16 *, 8) == 0) {
        temp_a0_2 = M2C_FIELD(arg2, u8 *, 0xE) | (M2C_FIELD(arg2, u8 *, 0xC) | M2C_FIELD(arg2, u8 *, 0xD));
        temp_a0_3 = temp_a0_2 + ((s32) (0xC0 - temp_a0_2) / (s16) M2C_FIELD(arg0, s16 *, 0xC));
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 1) {
            M2C_FIELD(arg2, u8 *, 0xC) = temp_a0_3;
        }
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 4) {
            M2C_FIELD(arg2, u8 *, 0xD) = temp_a0_3;
        }
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 2) {
            M2C_FIELD(arg2, u8 *, 0xE) = temp_a0_3;
        }
        temp_s0 = arg0 - 0x20;
        if (M2C_FIELD(arg0, s16 *, 0xC) >= 8) {
            func_801699CC(temp_s0, arg1, M2C_FIELD(arg0, void **, 0));
            func_801699CC(temp_s0, arg1, M2C_FIELD(arg0, void **, 0));
            func_801699CC(temp_s0, arg1, M2C_FIELD(arg0, void **, 0));
        }
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - 1;
        M2C_FIELD(arg0, s16 *, 0xC) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, s16 *, 0xC) = 8;
            M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + 1);
        }
    } else {
        temp_a0_4 = M2C_FIELD(arg2, u8 *, 0xE) | (M2C_FIELD(arg2, u8 *, 0xC) | M2C_FIELD(arg2, u8 *, 0xD));
        temp_a0_5 = temp_a0_4 + ((s32) -temp_a0_4 / (s16) M2C_FIELD(arg0, s16 *, 0xC));
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 1) {
            M2C_FIELD(arg2, u8 *, 0xC) = temp_a0_5;
        }
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 4) {
            M2C_FIELD(arg2, u8 *, 0xD) = temp_a0_5;
        }
        if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 2) {
            M2C_FIELD(arg2, u8 *, 0xE) = temp_a0_5;
        }
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - 1;
        M2C_FIELD(arg0, s16 *, 0xC) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
    }
}
