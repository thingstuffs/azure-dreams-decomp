#include "common.h"
#include "m2c_compat.h"

s32 func_8003DA40(s32, void *, s16 *, s16);         /* extern */
M2C_UNK func_80047454(void *);                      /* extern */
M2C_UNK func_800A4398(M2C_UNK);                     /* extern */

void func_80163898(void *arg0, void *arg1, void *arg2) {
    s16 sp10;
    s32 var_v0;
    s32 var_v1;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_v0_4;
    s8 temp_v0_5;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_3;
    void *temp_a1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v1;
    void *temp_v1_2;

    temp_s4 = M2C_FIELD(arg0, void **, 0xAC);
    temp_s2 = M2C_FIELD(temp_s4, void **, 0xC);
    temp_v1 = M2C_FIELD(temp_s4, void **, 8);
    if (!(M2C_FIELD(temp_s2, u16 *, 0x14) & 0x80)) {
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_v1, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_v1, u16 *, 6);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_v1, u16 *, 0xA);
    temp_a1 = M2C_FIELD(temp_s4, void **, 0xC);
    if (func_8003DA40(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp10, M2C_FIELD(arg0, s16 *, 0xB6)) != 0) {
        temp_v0 = sp10 + M2C_FIELD(arg0, s16 *, 0xB0);
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1));
        temp_v0_2 = sp12 + M2C_FIELD(arg0, s16 *, 0xB2);
        M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + ((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1));
        temp_v0_3 = sp14 + M2C_FIELD(arg0, s16 *, 0xB4);
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + ((s32) (temp_v0_3 + (temp_v0_3 >> 0x1F)) >> 1));
        M2C_FIELD(arg0, s16 *, 0xB0) = (s16) (u16) sp10;
        M2C_FIELD(arg0, s16 *, 0xB2) = (s16) (u16) sp12;
        M2C_FIELD(arg0, s16 *, 0xB4) = (s16) (u16) sp14;
    }
    temp_v1_2 = M2C_FIELD(arg2, void **, 8);
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_s2, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_s2, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) M2C_FIELD(temp_s2, u16 *, 0x14);
    M2C_FIELD(temp_v1_2, u8 *, 1) = (u8) (M2C_FIELD(temp_v1_2, u8 *, 1) & 0xFE);
    if (M2C_FIELD(arg0, s16 *, 0xB6) == 1) {
        temp_a0 = M2C_FIELD(temp_s2, s8 *, 4);
        if (temp_a0 < 8) {
            var_v0 = temp_a0 * 7;
        } else {
            var_v0 = (0xF - temp_a0) * 7;
        }
        temp_v0_4 = (var_v0 * 2) + 0x20;
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v0_4;
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v0_4;
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v0_4;
        if (!(M2C_FIELD(temp_s2, u16 *, 0x14) & 0x8000) && ((u16) M2C_FIELD(temp_s2, s8 *, 4) == 0x10C)) {
            func_800A4398(0x709);
        }
    }
    if (M2C_FIELD(arg0, s16 *, 0xB6) == 2) {
        temp_a0_2 = M2C_FIELD(temp_s2, s8 *, 4);
        if (temp_a0_2 < 8) {
            var_v1 = 7 - temp_a0_2;
        } else {
            var_v1 = temp_a0_2 - 8;
        }
        temp_v0_5 = (var_v1 * 0xE) + 0x20;
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v0_5;
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v0_5;
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v0_5;
        if (!(M2C_FIELD(temp_s2, u16 *, 0x14) & 0x8000) && ((u16) M2C_FIELD(temp_s2, s8 *, 4) == 0x104)) {
            func_800A4398(0x709);
        }
    }
    func_80047454(arg2);
    if (M2C_FIELD(temp_s4, u16 *, 0x1E) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800803D4 |= 0x8000;
    }
}
