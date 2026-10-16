#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800ACF88(void *);                      /* extern */
s16 func_800BCB04(u16, u16, s16, s16);              /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_8008346A;

void func_801671FC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE;
    temp_a3 = *(temp_v1 + &D_8006CCE8);
    if (temp_a1 < 5U) {
        switch (temp_a1) {
        case 1:
            break;
        case 0:
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF & 0xFFFBFFFF);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_v1 + &D_8006CCD8) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a3 << 0x10);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF40000;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            break;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x1C000);
        if (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA), temp_a3) >= 0x200) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
        }
        if (D_8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x14);
            if ((temp_v1_2 & 0x4000) && !(temp_v1_2 & 0x20000000)) {
                func_800ACF88(arg3);
            }
            func_800A56E0(0x805);
            M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x1C000);
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                M2C_FIELD(arg0, s16 *, 0x96) = 0x80;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            }
        }
    }
}
