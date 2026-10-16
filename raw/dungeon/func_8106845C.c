#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A48F0(void *, M2C_UNK, s8);         /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_80164F68();                            /* static */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80167FB8;
extern M2C_UNK D_80167FD0;
extern M2C_UNK D_80167FD8;
extern M2C_UNK D_80167FE0;

void func_80167C5C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_a1;
    s32 temp_v1_3;
    u16 temp_v1_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    switch (temp_v1) {
    case 0:
    case 4:
        func_800A56E0(0x51C);
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 7U;
            return;
        }
        if (temp_v1_2 & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80167FD8;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80167FD8), 0);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF00000;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
block_15:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
    default:
        return;
    case 1:
    case 5:
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xA0);
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - temp_v1_3);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) != 0) {
            M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (temp_v1_3 + M2C_FIELD(arg1, s32 *, 0x14));
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x30000);
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg0, s32 *, 0xA0));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
block_14:
            goto block_15;
        }
        break;
    case 2:
    case 6:
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        var_a1 = &D_80167FE0;
block_13:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
        goto block_14;
    case 3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_80167FD0;
            goto block_13;
        }
        break;
    case 7:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80167FB8;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80167FB8), 0);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80164F68;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
            M2C_FIELD(arg0, s16 *, 0xAE) = (s16) ((func_800A6D30() & 7) + 8);
            func_800A48F0(arg3, 0x1A, (s8) M2C_FIELD(arg0, s16 *, 0xAE));
        }
        break;
    }
}
