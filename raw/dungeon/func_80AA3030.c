#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8016AE7C;
extern M2C_UNK D_8016EC34;
extern M2C_UNK D_8016EC64;
extern M2C_UNK D_8016EC6C;

void func_8016C830(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_v0;
    s32 var_v1;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            return;
        }
        temp_v1_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
        temp_a0 = temp_v1_2 + 4;
        var_v0 = temp_a0;
        if (temp_a0 < 0) {
            var_v0 = temp_v1_2 + 0xB;
        }
        temp_a0_2 = (temp_a0 - (var_v0 & 0x18)) * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_a0_2 + &D_8006CCD8) * 0x30000);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_a0_2 + &D_8006CCE8) * 0x30000);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016EC34;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016EC34), 0);
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
block_16:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg1, s32 *, 0xC);
        temp_v1_3 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v0 - (temp_v0 >> 2));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v1_3 - (temp_v1_3 >> 2));
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016EC64;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016EC64), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            goto block_16;
        }
        return;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800A56E0(0x808);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016EC6C;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016EC6C), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0x14U;
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            goto block_16;
        }
        break;
    case 3:
        temp_v1_4 = M2C_FIELD(arg1, s32 *, 0x14);
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if ((s16) temp_v0_2 < 0xC) {
            var_v1 = temp_v1_4 + 0x1400;
        } else {
            var_v1 = temp_v1_4 + 0x20000;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = var_v1;
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + var_v1);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x11) {
            temp_a0_3 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
            temp_v0_3 = *(temp_a0_3 + &D_8006CCD8) * 0x30000;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v0_3 + (temp_v0_3 >> 2));
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF70000;
            temp_v0_4 = *(temp_a0_3 + &D_8006CCE8) * 0x30000;
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v0_4 + (temp_v0_4 >> 2));
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        }
        if (((M2C_FIELD(arg2, s8 *, 4) == 3) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
        }
        if (((M2C_FIELD(arg2, s8 *, 4) == 5) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016AE7C;
            *(s32 *)0x8008346C = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
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
