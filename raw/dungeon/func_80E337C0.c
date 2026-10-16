#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
s32 func_8003F270();                                /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_800BB044(void *);                      /* extern */
M2C_UNK func_8014D094();                            /* static */
void *func_80151858(void *, void *, void *);        /* static */
extern M2C_UNK D_8006DE24;
extern s32 D_800814A0;
extern void *D_800814A8;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_80152460;
extern M2C_UNK D_80152490;
extern M2C_UNK D_80152498;

void func_8014EFC0(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp18;
    u16 sp1A;
    u16 sp1C;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s5;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u8 *var_s0;
    u8 temp_v1;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 var_v0_3;
    void *temp_v0_10;
    void *temp_v0_4;
    void *temp_v1_3;
    void *var_v0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_s5 = 0;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            switch (temp_v0) {                      /* switch 2 */
            case 7:                                 /* switch 2 */
                var_s5 = 1;
                goto block_13;
            case 6:                                 /* switch 2 */
                var_s5 = 1;
                goto block_14;
            case 5:                                 /* switch 2 */
                var_s5 = 1;
                goto block_15;
            default:                                /* switch 2 */
                var_s0 = NULL;
                break;
            }
        } else {
            temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            if (temp_v1_2 != 2) {
                if (temp_v1_2 < 3) {
                    var_s0 = NULL;
                    if (temp_v1_2 != 1) {

                    } else {
                    case 1:                         /* switch 2 */
block_15:
                        var_s0 = arg3 + 8;
                    }
                } else {
                    var_s0 = NULL;
                    if (temp_v1_2 == 3) {
                    case 3:                         /* switch 2 */
block_13:
                        var_s0 = arg3 + 0xE;
                    }
                }
            } else {
            case 2:                                 /* switch 2 */
block_14:
                var_s0 = arg3 + 0xB;
            }
        }
        if (*var_s0 != 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
            if (var_s5 != 0) {
                var_v0 = D_800814A8;
                M2C_FIELD(arg3, void **, 0x60) = var_v0;
                goto block_22;
            }
            if (M2C_FIELD(((*var_s0 * 0x14) + &D_8006DE24), u8 *, 0x12) == 2) {
                var_v0 = M2C_FIELD(arg3, void **, 0x60);
                if (var_v0 != NULL) {
block_22:
                    temp_v1_3 = M2C_FIELD(var_v0, void **, -0x14);
                    M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x24);
                    M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x25);
                }
            } else {
                M2C_FIELD(arg3, void **, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
                var_v0_2 = M2C_FIELD(arg3, s8 *, 0x72);
                var_v1 = M2C_FIELD(arg3, s8 *, 0x73);
                if (var_v0_2 < 0) {
                    var_v0_2 = -var_v0_2;
                }
                if (var_v1 < 0) {
                    var_v1 = -var_v1;
                }
                M2C_FIELD(arg3, s8 *, 0x72) = var_v0_2;
                M2C_FIELD(arg3, s8 *, 0x73) = var_v1;
            }
            if (func_800A94A0(arg3, var_s0, var_s5, arg0 + 0x98) != 0) {
                func_800BB044(arg3);
                var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_49:
                M2C_FIELD(arg0, u8 *, 0x9B) = var_v0_3;
                return;
            }
        default:                                    /* switch 1 */
            return;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        D_8008346C = 0;
        M2C_FIELD(D_800814A8, u16 *, 0xA6) = (u16) (M2C_FIELD(D_800814A8, u16 *, 0xA6) - 1);
        func_800A4ACC(arg3);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8014D094;
        M2C_FIELD(arg3, s8 *, 0x73) = 0;
        M2C_FIELD(arg3, s8 *, 0x72) = 0;
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (func_8003F270() != 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        M2C_FIELD(arg0, u16 *, 0xAE) = 8U;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 2:                                         /* switch 1 */
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xAE) - 1;
        M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_2;
        if ((temp_v0_2 << 0x10) > 0) {
            temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x100;
            M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
            M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_3;
            return;
        }
        M2C_FIELD(arg0, void **, 0xA0) = func_80151858(arg0, arg1, arg2);
        temp_v0_4 = *((*((((s32) (M2C_FIELD(&D_80083160, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80152498) * 4) + **M2C_FIELD(arg2, s32 ***, 0x28));
        M2C_FIELD(arg2, void **, 0) = temp_v0_4;
        M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(temp_v0_4, s32 *, 4);
        sp1C = 0;
        sp1A = 0;
        sp18 = 0;
        if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp18, 0) != 0) {
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + sp18);
            M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + sp1A);
            M2C_FIELD(arg0, u16 *, 0xB2) = sp1C;
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) ((M2C_FIELD(arg1, u16 *, 0xA) - M2C_FIELD(arg3, u16 *, 0x88)) + ((s32) ((s16) sp1C + ((u32) (sp1C << 0x10) >> 0x1F)) >> 1));
        }
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xBFFFFFFF);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80152490;
        func_80047784(arg2, *((((s32) (M2C_FIELD(&D_80083160, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80152490), 0);
        M2C_FIELD(arg2, u16 *, 0x1E) = 0x800U;
        M2C_FIELD(arg2, u16 *, 0x1C) = 0x800U;
block_47:
        M2C_FIELD(arg0, u16 *, 0xAE) = 8U;
block_48:
        var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
        goto block_49;
    case 3:                                         /* switch 1 */
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 0xAE) - 1;
        M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_5;
        if (!(temp_v0_5 & 0x8000)) {
            temp_v0_6 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x100;
            M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_6;
            M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_6;
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + ((s32) (M2C_FIELD(arg0, u16 *, 0xB2) << 0x10) >> 0x14));
            return;
        }
        M2C_FIELD(arg0, u16 *, 0xAE) = 4U;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 4:                                         /* switch 1 */
        temp_v0_7 = M2C_FIELD(arg0, u16 *, 0xAE) - 1;
        M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_7;
        if (temp_v0_7 & 0x8000) {
            M2C_FIELD(arg0, s32 *, 0xB4) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
            M2C_FIELD(arg0, u16 *, 0xBA) = (u16) M2C_FIELD(arg2, u16 *, 0x10);
            M2C_FIELD(arg0, u16 *, 0xB8) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
            M2C_FIELD(arg0, u16 *, 0xAE) = 9U;
            goto block_48;
        }
        break;
    case 5:                                         /* switch 1 */
        temp_v0_8 = M2C_FIELD(arg0, u16 *, 0xAE) - 1;
        M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_8;
        if ((temp_v0_8 << 0x10) > 0) {
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
            M2C_FIELD(arg2, u16 *, 0x10) = (u16) (M2C_FIELD(arg2, u16 *, 0x10) | 0x20);
            temp_v1_4 = (u8) M2C_FIELD(arg2, s32 *, 0xC);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            M2C_FIELD(arg2, s32 *, 0xC) = (s8) (temp_v1_4 - ((s32) temp_v1_4 / (s16) M2C_FIELD(arg0, u16 *, 0xAE)));
            temp_v1_5 = M2C_FIELD(arg2, u8 *, 0xD);
            M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1_5 - ((s32) temp_v1_5 / (s16) M2C_FIELD(arg0, u16 *, 0xAE)));
            temp_v1_6 = M2C_FIELD(arg2, u8 *, 0xE);
            M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_v1_6 - ((s32) temp_v1_6 / (s16) M2C_FIELD(arg0, u16 *, 0xAE)));
            if ((s16) M2C_FIELD(arg0, u16 *, 0xAE) == 1) {
                goto block_47;
            }
        }
        break;
    case 6:                                         /* switch 1 */
        temp_v0_9 = M2C_FIELD(arg0, u16 *, 0xAE) - 1;
        M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_9;
        if (((temp_v0_9 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            temp_v0_10 = M2C_FIELD(arg0, void **, 0xA0);
            if (temp_v0_10 != NULL) {
                M2C_FIELD(arg0, s16 *, 0xAC) = 0;
                M2C_FIELD(arg0, s32 *, 0xA4) = 0;
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                D_800814A0 |= 0x8000;
                M2C_FIELD(temp_v0_10, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_v0_10, u16 *, 0x1E) | 0x8000);
                M2C_FIELD(arg0, void **, 0xA0) = NULL;
            }
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xEFFFFFFF);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 0xB8);
            M2C_FIELD(arg2, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xB4);
            M2C_FIELD(arg2, u16 *, 0x10) = (u16) M2C_FIELD(arg0, u16 *, 0xBA);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80152460) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80152460;
                func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80152460), 0);
            }
            if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8014D094;
                M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
                M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
                func_800A4ACC(arg3);
                M2C_FIELD(arg3, s8 *, 0x73) = 0;
                M2C_FIELD(arg3, s8 *, 0x72) = 0;
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                func_800A56E0(0xB4);
            }
        }
        break;
    }
}
