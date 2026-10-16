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
extern M2C_UNK D_801650F4;
extern M2C_UNK D_80168F30;

void func_80166908(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_s3;
    s16 temp_s4;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_v1;
    u16 temp_v0;
    u8 temp_a0;

    temp_v1 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s3 = *(temp_v1 + &D_8006CCD8);
    temp_a0 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s4 = *(temp_v1 + &D_8006CCE8);
    switch (temp_a0) {                              /* irregular */
    case 0x0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168F30;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168F30), 0);
block_14:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 0x1:
        if (((M2C_FIELD(arg2, s8 *, 4) == temp_a0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_800A56E0(0x808);
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF50000;
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((temp_s3 << 0x17) / 5);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((temp_s4 << 0x17) / 5);
            goto block_14;
        }
        return;
    case 0x2:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((s16) temp_v0 == 3) {
            func_8009C12C(arg3, arg2, (s16) M2C_FIELD(arg3, u16 *, 0x2A), 1);
        }
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + ((5 - (s16) M2C_FIELD(arg0, u16 *, 0x96)) << 0x10));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) < 3) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
        }
        temp_a1 = M2C_FIELD(arg1, s32 *, 0xC);
        temp_a2 = M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_a1 - ((temp_a1 * 4) / 5));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a2 - ((temp_a2 * 4) / 5));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = 0xFFU;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            return;
        }
        break;
    case 0xFF:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - (M2C_FIELD(arg1, s16 *, 2) - 0x20)) << 0xE);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - (M2C_FIELD(arg1, s16 *, 6) - 0x20)) << 0xE);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801650F4;
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
