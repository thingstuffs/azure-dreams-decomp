#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_801530EC();                            /* static */
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern void *D_800E3D7C;
extern M2C_UNK D_80157EB8;
extern M2C_UNK D_80157EC8;
extern M2C_UNK D_80157ED0;

void func_80154480(void *arg0, void *arg2, void *arg3) {
    M2C_UNK *var_a1;
    u16 temp_a0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        temp_a0 = M2C_FIELD(arg3, u16 *, 0x2A) & 0xFFF;
        M2C_FIELD(arg3, u16 *, 0x2A) = temp_a0;
        if (((0x400 - ((M2C_FIELD(&D_80083160, u16 *, 0xC8) + 0x100) & 0xE00)) & 0xE00) != temp_a0) {
            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (temp_a0 + 0x200);
            return;
        }
block_13:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg0, s16 *, 0x92) != 0) {
            var_a1 = &D_80157EC8;
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                goto block_12;
            }
        default:
            return;
        }
block_11:
        var_a1 = &D_80157EC8;
block_12:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
        func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
        goto block_13;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_80157ED0;
            goto block_12;
        }
        break;
    case 3:
        if ((M2C_FIELD(&D_80083160, u16 *, 8) != 0) || (M2C_FIELD(D_800E3D7C, u8 *, 0x9A) != 0x17)) {
            goto block_11;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157EB8;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157EB8), 0);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801530EC;
            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0xB0);
            M2C_FIELD(arg0, s16 *, 0xB2) = 0;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
        }
        break;
    }
}
