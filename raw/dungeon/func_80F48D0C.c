#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s16 func_800A70E4(s16, s16, s16);                   /* extern */
void *func_800A8608(void *, void *, s32, s32, s32); /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;
extern M2C_UNK D_8015EE94;
extern M2C_UNK D_801623E8;
extern M2C_UNK D_80162A74;
extern M2C_UNK D_80162AE4;
extern M2C_UNK D_80162AEC;

void func_8016250C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_s4;
    s32 temp_v0_5;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_s4;
    s32 var_v1;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_6;
    u8 temp_v1;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_s4 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
        M2C_FIELD(arg0, u16 *, 0xA8) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(arg0, u16 *, 0xAA) = (u16) M2C_FIELD(arg1, u16 *, 6);
        temp_v1_2 = temp_s4 * 2;
        temp_v0 = func_800A70E4((s16) (M2C_FIELD(arg2, u8 *, 0x24) + *(temp_v1_2 + &D_8006CCD8)), (s16) (M2C_FIELD(arg2, u8 *, 0x25) + *(temp_v1_2 + &D_8006CCE8)), M2C_FIELD(arg3, s16 *, 0x88));
        temp_s1 = (temp_v0 * 4) + &D_800E3548;
        if (M2C_FIELD(temp_s1, u8 *, 1) == 0x12) {
            M2C_FIELD(arg3, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(temp_s1, s8 *, 0));
            temp_s0 = (temp_v0 * 0xC) + &D_800E36C8;
            temp_v0_2 = func_800A8608(arg0 - 0x20, temp_s1, (M2C_FIELD(temp_s0, u8 *, 0) << 6) | 0x20, (M2C_FIELD(temp_s0, u8 *, 1) << 6) | 0x20, (s32) M2C_FIELD(arg1, s16 *, 0xA));
            if (temp_v0_2 != NULL) {
                M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_801623E8;
                M2C_FIELD(temp_v0_2, s8 *, 0xBB) = 0;
            }
            M2C_FIELD(temp_s1, s8 *, 0) = 0;
            M2C_FIELD(temp_s1, u8 *, 1) = 0U;
            func_8009A3D0(M2C_FIELD(temp_s0, u8 *, 0), M2C_FIELD(temp_s0, u8 *, 1), 0x800);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            return;
        }
        temp_a0 = temp_s4 * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_a0 + &D_8006CCD8) * 0x18000);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_a0 + &D_8006CCE8) * 0x18000);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162AE4;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162AE4), 0);
        func_800A56E0(0x51E);
        var_v1 = 0x7D0;
block_30:
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) var_v1;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) && ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x3E9)) {
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
        }
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
        if (temp_v0_3 & 0x8000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162AEC;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162AEC), 0);
            var_v1 = 0x7D0;
            goto block_30;
        }
        return;
    case 2:
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) && ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x3E9)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0xCU;
        }
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if (temp_v0_4 & 0x8000) {
            temp_v1_3 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_v1_3 + &D_8006CCD8) * -0x10000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_v1_3 + &D_8006CCE8) * -0x10000);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80162A74;
            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80162A74), 0);
            temp_v1_4 = (s16) M2C_FIELD(arg0, u16 *, 0xAA) - (s16) M2C_FIELD(arg1, u16 *, 6);
            var_s4 = temp_v1_4;
            if (temp_v1_4 < 0) {
                var_s4 = -var_s4;
            }
            temp_v0_5 = (s16) M2C_FIELD(arg0, u16 *, 0xA8) - (s16) M2C_FIELD(arg1, u16 *, 2);
            var_v1 = temp_v0_5;
            if (temp_v0_5 < 0) {
                var_v1 = -var_v1;
            }
            if (var_v1 < var_s4) {
                var_v1 = var_s4;
            }
            goto block_30;
        }
        break;
    case 3:
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0) = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0xA8) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 4) = (s32) ((s16) M2C_FIELD(arg0, u16 *, 0xAA) << 0x10);
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015EE94;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
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
