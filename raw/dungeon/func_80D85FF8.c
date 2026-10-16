#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s32 func_800BCB04(u16, u16, s16);                   /* extern */
M2C_UNK func_80153F1C();                            /* static */
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_800E2380;
extern M2C_UNK D_800E2388;

void func_801557F8(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    u16 temp_v0_2;
    u16 var_v0;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 4U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        if (M2C_FIELD(arg0, s16 *, 0x92) == (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) - M2C_FIELD(arg3, u16 *, 0x88))) {
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
            var_v0 = M2C_FIELD(arg2, u16 *, 0x14) | 0xC;
block_20:
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0;
        }
    default:
        return;
    case 1:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2380;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2380), 0);
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if (((s16) temp_v0 == 0xA) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 9) {
            func_800A56E0(0x809);
            return;
        }
        break;
    case 3:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) > 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
            if ((temp_v0_2 << 0x10) == 0) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2388;
                func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2388), 0);
                return;
            }
        } else {
            if (M2C_FIELD(arg0, s16 *, 0x92) >= -0x1F) {
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) - 4);
                return;
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 4:
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
                func_800AD594(arg3, 0x100);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80153F1C;
                D_8008346C = 0;
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
                var_v0 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFF3;
                goto block_20;
            }
        }
        break;
    }
}
