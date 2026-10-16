#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80044A50(void *);                      /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_8009929C(M2C_UNK, s32);                    /* extern */
s32 func_80099734(void *, s32);                     /* extern */
M2C_UNK func_8009A028(void *);                      /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
void *func_8009B25C(void *, s32, s32, s16);         /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
s16 func_800A70E4(s16, s16, s16);                   /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800BC318(void *);                      /* extern */
M2C_UNK func_80152EE4();                            /* static */
M2C_UNK func_8015598C();                            /* static */
M2C_UNK func_80157DD0(void *, M2C_UNK, void *, M2C_UNK); /* static */
s32 func_8015818C(void *, M2C_UNK, void *, void *); /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;
extern M2C_UNK D_8015286C;
extern M2C_UNK D_80152898;

void func_80155D78(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_s5;
    s16 temp_s6;
    s16 temp_v0_4;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v1_3;
    u16 temp_v0;
    u16 temp_v1_2;
    u8 temp_a1;
    u8 temp_a3;
    u8 temp_t1;
    u8 temp_v1;
    u8 temp_v1_4;
    u8 temp_v1_5;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (temp_v1_2 & 0xE000) {
            if (!(temp_v1_2 & 0x8000)) {
                func_800A56E0(0x80D);
            }
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0U;
                return;
            }
            M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
            return;
        }
    default:
        return;
    case 1:
        if (!(M2C_FIELD(arg0, u16 *, 0x96) & 3) && !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_80157DD0(arg0, arg1, arg2, 0);
            func_80157DD0(arg0, arg1, arg2, 1);
        }
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            temp_v1_3 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
            M2C_FIELD(arg3, void **, 0x60) = NULL;
            temp_s5 = M2C_FIELD(arg2, u8 *, 0x24) + *(temp_v1_3 + &D_8006CCD8);
            temp_s6 = M2C_FIELD(arg2, u8 *, 0x25) + *(temp_v1_3 + &D_8006CCE8);
            if (M2C_FIELD(arg0, u8 *, 0xAC) == 0) {
                temp_v0_2 = func_8009B25C(arg3, temp_s5 & 0xFFFF, temp_s6 & 0xFFFF, M2C_FIELD(arg3, s16 *, 0x88));
                M2C_FIELD(arg3, void **, 0x60) = temp_v0_2;
                if ((temp_v0_2 != NULL) && ((temp_v1_4 = M2C_FIELD(temp_v0_2, u8 *, 0x13), (((u32) (temp_v1_4 - 1) < 0x2DU) == 0)) || (temp_v1_4 == 0x1E))) {
                    temp_v0_3 = func_800990FC();
                    func_80099290(func_80099194(&D_80152898, func_80099734(temp_v0_2, func_8009929C(0xA, func_80099194(&D_8015286C, func_80099734(arg3, temp_v0_3))))));
                    func_800A5720(temp_v0_3);
                    func_800A56E0(0x506);
                    M2C_FIELD(arg3, void **, 0x60) = NULL;
                }
            }
            if (M2C_FIELD(arg0, u8 *, 0xAC) < 2U) {
                if (M2C_FIELD(arg3, void **, 0x60) == NULL) {
                    temp_v0_4 = func_800A70E4(temp_s5, temp_s6, M2C_FIELD(arg3, s16 *, 0x88));
                    if (temp_v0_4 >= 0) {
                        M2C_FIELD(arg3, void **, 0x60) = (void *) (temp_v0_4 + 1);
                    }
                    goto block_22;
                }
                goto block_24;
            }
block_22:
            if (M2C_FIELD(arg3, void **, 0x60) == NULL) {
                func_800A9A0C(arg3);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80152EE4;
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xEFFFFFFF);
                return;
            }
block_24:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 2:
            var_a2 = 0x3000;
            if (M2C_FIELD(arg3, s32 *, 0x14) & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000);
            temp_v0_5 = func_8015818C(arg0, arg1, arg2, arg3);
            M2C_FIELD(arg0, s32 *, 0xA4) = temp_v0_5;
            if (temp_v0_5 != 0) {
                temp_s0 = arg0 - 0x20;
                func_80044A50(temp_s0);
                func_8004491C(temp_s0, &D_800C6AEC);
                M2C_FIELD(arg2, u8 *, 0xF) = 0U;
                M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
                func_8009A028(arg3);
                M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) | 0x80000000);
block_35:
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                return;
            }
            var_a2_2 = 0x3000;
            if (M2C_FIELD(arg3, s32 *, 0x14) & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFEFFFF);
            return;
        }
        break;
    case 3:
        temp_v1_5 = M2C_FIELD(arg2, u8 *, 0xF);
        if (temp_v1_5 < 7U) {
            temp_t1 = M2C_FIELD(arg2, u8 *, 0xC);
            M2C_FIELD(arg2, u8 *, 0xF) = (u8) (temp_v1_5 + 1);
            temp_a3 = M2C_FIELD(arg2, u8 *, 0xD);
            temp_a1 = M2C_FIELD(arg2, u8 *, 0xE);
            M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_t1 + ((s32) -(s32) temp_t1 / (s32) (8 - M2C_FIELD(arg2, u8 *, 0xF))));
            M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_a3 + ((s32) -(s32) temp_a3 / (s32) (8 - M2C_FIELD(arg2, u8 *, 0xF))));
            M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_a1 + ((s32) -(s32) temp_a1 / (s32) (8 - M2C_FIELD(arg2, u8 *, 0xF))));
            return;
        }
        temp_s0_2 = arg0 - 0x20;
        func_80044A50(temp_s0_2);
        func_800BC318(temp_s0_2);
        M2C_FIELD(arg2, u8 *, 0xF) = 0U;
        M2C_FIELD(arg2, u8 *, 0xC) = 0x808080;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) + 0x80);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFF3);
        goto block_35;
    case 4:
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x18;
        M2C_FIELD(arg0, u8 *, 0x9B) = 0U;
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8015598C;
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
        M2C_FIELD(arg3, s8 *, 0x6D) = 0;
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xEFFFFFFF);
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        break;
    }
}
