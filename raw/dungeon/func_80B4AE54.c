#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s32 func_800BCB04(s32, s32, s16);                   /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8016AE70;
extern M2C_UNK D_8016DF38;
extern M2C_UNK D_8016DFDC;
extern M2C_UNK D_8016FA4C;
extern M2C_UNK D_8016FA8C;

void func_8016C654(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    s16 temp_s5;
    s16 temp_s6;
    s32 temp_v1;
    u16 temp_v1_2;
    u8 temp_s0;
    void *temp_s0_2;
    void *temp_v0;

    temp_s0 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s5 = *(temp_v1 + &D_8006CCD8);
    temp_s6 = *(temp_v1 + &D_8006CCE8);
    temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v1_2;
    switch (temp_s0) {                              /* irregular */
    case 0x0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s5 * -0x20000);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s6 * -0x20000);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016FA4C;
        func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016FA4C), 0);
        M2C_FIELD(arg0, u16 *, 0x96) = 8U;
block_26:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 0x1:
        if ((temp_v1_2 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016FA8C;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016FA8C), 0);
block_25:
            goto block_26;
        }
        return;
    case 0x2:
        if (((M2C_FIELD(arg2, s8 *, 4) == 4) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
            if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp10, 0) == 0) {
                sp14 = 0;
                sp12 = 0;
                sp10 = 0;
            }
            temp_v0 = func_8003FD64(0x12, &D_80083498);
            if (temp_v0 != NULL) {
                func_8004491C(temp_v0, &D_8016DFDC);
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016DF38;
                M2C_FIELD(temp_v0, s16 *, 0x20) = (s16) (M2C_FIELD(arg1, u16 *, 2) + sp10);
                temp_s0_2 = temp_v0 + 0x20;
                M2C_FIELD(temp_s0_2, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 6) + sp12);
                M2C_FIELD(temp_s0_2, s32 *, 8) = 0xC0C0C0;
                M2C_FIELD(temp_s0_2, s16 *, 0xE) = 8;
                M2C_FIELD(temp_s0_2, s16 *, 4) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) + sp14);
                M2C_FIELD(temp_s0_2, s16 *, 0x12) = (s16) (func_800BCB04(((M2C_FIELD(arg2, u8 *, 0x24) + temp_s5) << 6) & 0xFFC0, ((M2C_FIELD(arg2, u8 *, 0x25) + temp_s6) << 6) & 0xFFC0, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80)) - M2C_FIELD(arg1, u16 *, 0xA));
                M2C_FIELD(temp_s0_2, u16 *, 0x10) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
            }
            goto block_25;
        }
        break;
    case 0x3:
        if ((s16) temp_v1_2 == 0xA) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            func_800A56E0(0x813);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 8U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            goto block_25;
        }
        break;
    case 0x4:
        if ((temp_v1_2 << 0x10) <= 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8016FA4C;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8016FA4C), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = (u16) temp_s0;
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            return;
        }
        break;
    case 0xFF:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 0)) >> 1);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 4)) >> 1);
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) || ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0)) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016AE70;
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
