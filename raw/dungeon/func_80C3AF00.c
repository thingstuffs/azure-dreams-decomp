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
extern M2C_UNK D_8014D3A8;
extern M2C_UNK D_8015049C;
extern M2C_UNK D_801504B4;
extern M2C_UNK D_801504BC;
extern M2C_UNK D_801504C4;
extern M2C_UNK D_801504CC;

void func_8014E700(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_s4;
    s16 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_4;
    u16 temp_v1_3;
    u8 temp_v1_2;

    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s4 = *(temp_v1 + &D_8006CCD8);
    temp_s5 = *(temp_v1 + &D_8006CCE8);
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    switch (temp_v1_2) {                            /* irregular */
    case 0x0:
        temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_3 & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            return;
        }
        if (temp_v1_3 & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801504B4;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801504B4), 0);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s4 * -0x40000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s5 * -0x40000);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF & 0xFFFBFFFF);
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg1, s32 *, 0x14) = -0x18000;
block_24:
block_25:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 0x1:
        temp_v0 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (temp_v0 + (temp_v0 >> 2));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 8U;
            goto block_25;
        }
        break;
    case 0x2:
        temp_v0_2 = M2C_FIELD(arg1, s32 *, 0xC);
        temp_v1_4 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v0_2 - (temp_v0_2 >> 3));
        temp_v0_3 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v1_4 - (temp_v1_4 >> 3));
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (temp_v0_3 - (temp_v0_3 >> 3));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 4) {
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801504BC;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801504BC), 0);
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s4 * 0x60000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s5 * 0x60000);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801504C4;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801504C4), 0);
            goto block_24;
        }
        break;
    case 0x3:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + 0x80000);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) + (temp_s4 << 0x12));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) + (temp_s5 << 0x12));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 2) {
            func_800A56E0(0x809);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            goto block_24;
        }
        break;
    case 0x4:
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + 0x80000);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801504CC;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801504CC), 0);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            return;
        }
        break;
    case 0xFF:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0xF) >> 1);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0xF) >> 1);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014D3A8;
            *(s32 *)0x8008346C = 0;
            func_800A4ACC(arg3);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015049C;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015049C), 0);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                return;
            }
            *(void **)0x800E3DE8 = arg3 - 0x20;
        }
        break;
    }
}
