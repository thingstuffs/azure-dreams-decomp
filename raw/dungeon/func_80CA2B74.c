#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80167CFC(void *, void *, M2C_UNK, s32); /* extern */

void func_80168374(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_a0;
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 temp_v1;
    s16 temp_v1_3;
    s16 var_s1;
    s32 temp_v1_2;
    s32 var_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_a0_2;
    u8 temp_a0_3;
    u8 temp_a1;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 temp_v1_4;
    u8 temp_v1_5;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1C);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x2C);
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x26) + 1;
        M2C_FIELD(arg0, u16 *, 0x26) = temp_v0;
        temp_v1_2 = (s16) temp_v0 - temp_a0;
        if (((s16) temp_v0 >= temp_a0) && (temp_v1_2 < 7)) {
            temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x2C);
            temp_a0_2 = (M2C_FIELD(arg0, u8 *, 0) * temp_v1_2) / 6;
            M2C_FIELD(arg0, u8 *, 0x10) = temp_a0_2;
            M2C_FIELD(arg0, u8 *, 0xC) = temp_a0_2;
            M2C_FIELD(arg0, u8 *, 8) = temp_a0_2;
            M2C_FIELD(arg0, u8 *, 4) = temp_a0_2;
            temp_a1 = (M2C_FIELD(arg0, u8 *, 1) * ((s16) M2C_FIELD(arg0, u16 *, 0x26) - temp_v1_3)) / 6;
            M2C_FIELD(arg0, u8 *, 0x11) = temp_a1;
            M2C_FIELD(arg0, u8 *, 0xD) = temp_a1;
            M2C_FIELD(arg0, u8 *, 9) = temp_a1;
            M2C_FIELD(arg0, u8 *, 5) = temp_a1;
            temp_v1_4 = (M2C_FIELD(arg0, u8 *, 2) * ((s16) M2C_FIELD(arg0, u16 *, 0x26) - temp_v1_3)) / 6;
            M2C_FIELD(arg0, u8 *, 0x12) = temp_v1_4;
            M2C_FIELD(arg0, u8 *, 0xE) = temp_v1_4;
            M2C_FIELD(arg0, u8 *, 0xA) = temp_v1_4;
            M2C_FIELD(arg0, u8 *, 6) = temp_v1_4;
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x26) >= 0x22) {
            M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
        }
        break;
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x2A) < 4) {
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x26) + 1;
            M2C_FIELD(arg0, u16 *, 0x26) = temp_v0_2;
            if (((s16) temp_v0_2 + M2C_FIELD(arg0, s16 *, 0x2A)) == 0x2D) {
                M2C_FIELD(arg0, u8 *, 0x12) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0xE) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0xA) = 0x80U;
                M2C_FIELD(arg0, u8 *, 6) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0x11) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0xD) = 0x80U;
                M2C_FIELD(arg0, u8 *, 9) = 0x80U;
                M2C_FIELD(arg0, u8 *, 5) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0x10) = 0x80U;
                M2C_FIELD(arg0, u8 *, 0xC) = 0x80U;
                M2C_FIELD(arg0, u8 *, 8) = 0x80U;
                M2C_FIELD(arg0, u8 *, 4) = 0x80U;
            } else {
                temp_v0_3 = M2C_FIELD(arg0, u8 *, 0);
                temp_v1_5 = M2C_FIELD(arg0, u8 *, 1);
                temp_a0_3 = M2C_FIELD(arg0, u8 *, 2);
                M2C_FIELD(arg0, u8 *, 0x10) = temp_v0_3;
                M2C_FIELD(arg0, u8 *, 0xC) = temp_v0_3;
                M2C_FIELD(arg0, u8 *, 8) = temp_v0_3;
                M2C_FIELD(arg0, u8 *, 4) = temp_v0_3;
                M2C_FIELD(arg0, u8 *, 0x11) = temp_v1_5;
                M2C_FIELD(arg0, u8 *, 0xD) = temp_v1_5;
                M2C_FIELD(arg0, u8 *, 9) = temp_v1_5;
                M2C_FIELD(arg0, u8 *, 5) = temp_v1_5;
                M2C_FIELD(arg0, u8 *, 0x12) = temp_a0_3;
                M2C_FIELD(arg0, u8 *, 0xE) = temp_a0_3;
                M2C_FIELD(arg0, u8 *, 0xA) = temp_a0_3;
                M2C_FIELD(arg0, u8 *, 6) = temp_a0_3;
            }
        }
        if (M2C_FIELD(arg0, s16 *, 0x24) < 0xC) {
            M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + 1);
            M2C_FIELD(arg0, s32 *, 0x94) = (s32) ((M2C_FIELD(arg0, s16 *, 0x44) + M2C_FIELD(arg0, s16 *, 0x56)) << 0xF);
            M2C_FIELD(arg0, s32 *, 0x98) = (s32) ((M2C_FIELD(arg0, s16 *, 0x46) + M2C_FIELD(arg0, s16 *, 0x58)) << 0xF);
            M2C_FIELD(arg0, s32 *, 0x9C) = (s32) ((M2C_FIELD(arg0, s16 *, 0x48) + M2C_FIELD(arg0, s16 *, 0x5A) + 0x40) << 0xF);
            if (M2C_FIELD(arg0, s16 *, 0x2A) == 0) {
                var_s1 = 1;
                var_a3 = 1 << 0x1A;
                do {
                    func_80167CFC(arg0, arg1, arg2, var_a3 >> 0x10);
                    temp_v0_4 = var_s1 + 1;
                    var_s1 = temp_v0_4;
                    var_a3 = var_s1 << 0x1A;
                } while (temp_v0_4 < 8);
            }
        }
        break;
    case 2:
        temp_v0_5 = (M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x24)) / 10;
        M2C_FIELD(arg0, u8 *, 0x12) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0xE) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0xA) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 6) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0x11) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0xD) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 9) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 5) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0x10) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 0xC) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 8) = temp_v0_5;
        M2C_FIELD(arg0, u8 *, 4) = temp_v0_5;
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x94));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x98));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x9C));
        break;
    }
    temp_v0_6 = (u16) M2C_FIELD(arg0, s16 *, 0x24) - 1;
    M2C_FIELD(arg0, s16 *, 0x24) = temp_v0_6;
    if ((temp_v0_6 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
