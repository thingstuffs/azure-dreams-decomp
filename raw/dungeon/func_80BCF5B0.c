#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_801659DC();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_8016864C;
extern M2C_UNK D_80168654;
extern M2C_UNK D_8016865C;
extern M2C_UNK D_80168664;

void func_80166DB0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0_2;
    s32 temp_a0;
    s32 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        if (M2C_FIELD(arg0, s32 *, 0xA4) == 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016864C;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016864C), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 8U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
    default:
        return;
    case 1:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 - 1);
        if (((temp_v0 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168654;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168654), 0);
            func_800A56E0(0x707);
            M2C_FIELD(arg0, u16 *, 0x96) = 6U;
            M2C_FIELD(arg0, s32 *, 0xAC) = 0x80000;
            M2C_FIELD(arg0, s32 *, 0xB0) = 0xFFFE0000;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCD8) * -0x40000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCE8) * -0x40000);
            return;
        }
        break;
    case 2:
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0xAC);
        M2C_FIELD(arg0, s32 *, 0xA4) = (s32) (M2C_FIELD(arg0, s32 *, 0xA4) + temp_v1_2);
        M2C_FIELD(arg0, s32 *, 0xAC) = (s32) (temp_v1_2 + M2C_FIELD(arg0, s32 *, 0xB0));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 2) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCD8) << 0x13);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE) + &D_8006CCE8) << 0x13);
        }
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_2 - 1);
        if (((temp_v0_2 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800A56E0(0x804);
            return;
        }
        break;
    case 3:
        temp_a0 = M2C_FIELD(arg0, s32 *, 0xAC);
        M2C_FIELD(arg0, s32 *, 0xA4) = (s32) (M2C_FIELD(arg0, s32 *, 0xA4) + temp_a0);
        M2C_FIELD(arg0, s32 *, 0xAC) = (s32) (temp_a0 + M2C_FIELD(arg0, s32 *, 0xB0));
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016865C;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016865C), 0);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, s32 *, 0xA4) = 0;
            return;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168664;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168664), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg0, s32 *, 0xA4) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
            return;
        }
        break;
    case 5:
        temp_a0_2 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        if (temp_a0_2 != 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0x10) / temp_a0_2);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
        }
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801659DC;
            D_8008346C = 0;
            func_800A4ACC(arg3);
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s16 *, 2) = (s16) ((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20);
            M2C_FIELD(arg1, s16 *, 6) = (s16) ((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20);
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        }
        break;
    }
}
