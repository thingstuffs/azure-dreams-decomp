#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_8016AE9C();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_8016EF30;
extern M2C_UNK D_8016EF38;
extern M2C_UNK D_8016EF40;

void func_8016C524(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_a1;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCD8) << 0x14);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCE8) << 0x14);
block_20:
block_21:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 1);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 1);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_8016EF30;
block_19:
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
            goto block_20;
        }
    default:
        return;
    case 2:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 1);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 1);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800A56E0(0x808);
            var_a1 = &D_8016EF38;
            goto block_19;
        }
        break;
    case 3:
        if ((M2C_FIELD(arg2, s8 *, 4) == 2) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) {
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            M2C_FIELD(arg0, u16 *, 0x96) = 6U;
            goto block_21;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016EF40;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016EF40), 0);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            return;
        }
        break;
    case 4:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((s16) temp_v0 > 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / (s16) temp_v0);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
        } else {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            var_a1 = &D_8016EF40;
            goto block_19;
        }
        break;
    case 5:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if ((s16) temp_v0_2 > 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / (s16) temp_v0_2);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
        } else {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8016AE9C;
            D_8008346C = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            func_800A4ACC(arg3);
        }
        break;
    }
}
