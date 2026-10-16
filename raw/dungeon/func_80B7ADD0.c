#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s32 func_800BCB04(s32, s32, s16);                   /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80164E5C;
extern M2C_UNK D_80167D04;
extern M2C_UNK D_80167D34;

void func_801665D0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_s4;
    s16 temp_s5;
    s16 var_v0;
    s32 temp_v1;
    u16 temp_a0;
    u16 var_v1;
    u8 temp_v1_2;
    u8 var_v0_2;
    void *temp_v0;

    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s4 = *(temp_v1 + &D_8006CCD8);
    temp_s5 = *(temp_v1 + &D_8006CCE8);
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_a0;
    switch (temp_v1_2) {                            /* irregular */
    case 0x0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80167D34;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80167D34), 0);
        temp_v0 = M2C_FIELD(arg3, void **, 0x60);
        if (temp_v0 != NULL) {
            var_v0 = M2C_FIELD(M2C_FIELD(temp_v0, void **, -0x18), u16 *, 0xA) - 0x34;
        } else {
            var_v0 = func_800BCB04(((M2C_FIELD(arg2, u8 *, 0x24) + temp_s4) << 6) & 0xFFC0, ((M2C_FIELD(arg2, u8 *, 0x25) + temp_s5) << 6) & 0xFFC0, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0xA0)) - 0x34;
        }
        M2C_FIELD(arg0, s16 *, 0xA6) = var_v0;
        var_v1 = 2;
block_18:
        M2C_FIELD(arg0, u16 *, 0x96) = var_v1;
        var_v0_2 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_19:
        M2C_FIELD(arg0, u8 *, 0x9B) = var_v0_2;
        return;
    case 0x1:
        M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + ((M2C_FIELD(arg0, s16 *, 0xA6) - M2C_FIELD(arg1, s16 *, 0xA)) / 3));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
            M2C_FIELD(arg0, u16 *, 0x92) = -0x18U;
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_s4 << 0x16) / 4);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (temp_s5 << 0x16) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
            var_v0_2 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_19;
        }
        return;
    case 0x2:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + (((M2C_FIELD(arg0, s16 *, 0xA6) - M2C_FIELD(arg1, s16 *, 0xA)) / 3) << 0x10));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            var_v1 = 0xA;
            goto block_18;
        }
        break;
    case 0x3:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - (((s32) (temp_a0 << 0x10) >> 4) + 0x2000));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 6) {
            func_800A56E0(0x808);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 2) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s4 * -0x80000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s5 * -0x80000);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF80000;
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            return;
        }
        break;
    case 0xFF:
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x18000);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80167D04;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80167D04), 0);
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164E5C;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                return;
            }
            *(void **)0x800E3DE8 = arg3 - 0x20;
        }
        break;
    }
}
