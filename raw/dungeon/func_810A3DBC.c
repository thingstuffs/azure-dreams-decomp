#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_80152E94();                            /* static */
s32 func_8015789C(void *, void *, void *);          /* static */
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80157F10;
extern M2C_UNK D_80157F40;
extern M2C_UNK D_80157F68;

void func_801555BC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 var_v0;
    u16 temp_a0;
    u16 temp_v0;
    u16 temp_v1_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F40;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F40), 0);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
block_12:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
    default:
        return;
    case 1:
        temp_a0 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_a0 & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 4U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            if (M2C_FIELD(arg0, u8 *, 0xAE) == 2) {
                func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
                return;
            }
        } else if ((M2C_FIELD(arg2, s8 *, 4) == 2) && (temp_a0 & 0x1000)) {
            func_800A56E0(0x808);
            M2C_FIELD(arg0, s32 *, 0xB0) = func_8015789C(arg0, arg1, arg2);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F68;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F68), 0);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            goto block_12;
        }
        break;
    case 3:
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0x8000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F68;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F68), 0);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        var_v0 = temp_v1_2 & 0x6000;
block_17:
        if (var_v0 != 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F10;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F10), 0);
            M2C_FIELD(arg0, u8 *, 0xAE) = 0U;
            M2C_FIELD(arg3, s32 *, 0x14) = (s32) (M2C_FIELD(arg3, s32 *, 0x14) & 0xBFFFFFFF);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x800);
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80152E94;
            D_8008346C = 0;
        }
        break;
    case 4:
        var_v0 = M2C_FIELD(arg2, u16 *, 0x14) & 0xE000;
        goto block_17;
    }
}
