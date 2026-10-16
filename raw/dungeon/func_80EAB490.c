#include "common.h"
#include "m2c_compat.h"

s32 func_8003F270(s16 *);                           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *, u16, u16, u16); /* extern */
M2C_UNK func_800DB2DC(void *, void *, void *, M2C_UNK); /* extern */
M2C_UNK func_801530F4();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_80156EF8;
extern M2C_UNK D_80156F00;

void func_80154C90(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 *temp_a0_2;
    s16 temp_s6;
    s16 temp_s7;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s5;
    s32 var_v0_4;
    s8 var_v0_2;
    s8 var_v1;
    u16 var_v0_5;
    u8 *var_s0;
    u8 temp_v1;
    u8 var_v0_3;
    void *temp_v1_3;
    void *var_v0;

    temp_a0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_a0_2 = temp_a0 + &D_8006CCE8;
    temp_s6 = *(temp_a0 + &D_8006CCD8);
    temp_s7 = *temp_a0_2;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    var_s5 = 0;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        M2C_FIELD(arg0, u16 *, 0xAC) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
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
                M2C_FIELD(arg3, void **, 0x60) = func_800A05A4(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A), 0x10);
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
            if (func_800A94A0(arg3, var_s0, var_s5, arg0 + 0x98, M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, u16 *, 0xA)) != 0) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                func_800A56E0(0x703);
                func_800DB2DC(arg1, arg2, arg3, 0xA);
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                M2C_FIELD(arg0, u16 *, 0x96) = 2U;
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
                M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s6 * -0xC0000);
                M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s7 * -0xC0000);
                M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF30000;
                var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_51:
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
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801530F4;
        M2C_FIELD(arg3, s8 *, 0x73) = 0;
        M2C_FIELD(arg3, s8 *, 0x72) = 0;
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 0x10U;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
            return;
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s6 << 0x12);
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s7 << 0x12);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF30000;
            var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_51;
        }
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) * 2);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) * 2);
        return;
    case 2:                                         /* switch 1 */
        if (func_8003F270(temp_a0_2) != 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 3:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x30000);
        if (((M2C_FIELD(arg2, s8 *, 4) == 4) && (var_v0_4 = temp_s6 << 0x13, ((M2C_FIELD(arg2, u16 *, 0x14) & 0x1000) != 0))) || (var_v0_4 = temp_s6 << 0x13, ((M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) != 0))) {
            M2C_FIELD(arg1, s32 *, 0xC) = var_v0_4;
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s7 << 0x13);
            var_v0_5 = M2C_FIELD(arg0, u16 *, 0x98) | 0x80;
block_48:
            M2C_FIELD(arg0, u16 *, 0x98) = var_v0_5;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 4:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x20000);
        if (((M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000) && ((s16) M2C_FIELD(arg0, u16 *, 0xAC) >= (s16) M2C_FIELD(arg1, u16 *, 0xA))) || ((s16) M2C_FIELD(arg0, u16 *, 0xAC) < (s16) M2C_FIELD(arg1, u16 *, 0xA))) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x96) = 4U;
            M2C_FIELD(arg2, s16 *, 0x1C) = 0x1400;
            M2C_FIELD(arg2, s16 *, 0x1E) = 0xC00;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156F00;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156F00), 0);
            var_v0_5 = M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7;
            goto block_48;
        }
        break;
    case 5:                                         /* switch 1 */
        temp_v0_2 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        temp_lo = temp_v0_2 * temp_v0_2;
        M2C_FIELD(arg2, s16 *, 0x1C) = (s16) ((temp_lo * 0x12C) + 0x1000);
        M2C_FIELD(arg2, s16 *, 0x1E) = (s16) (0x1000 - (temp_lo * 0xC8));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156EF8;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156EF8), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
            var_v0_3 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
            goto block_51;
        }
        break;
    case 6:                                         /* switch 1 */
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) - ((s16) M2C_FIELD(arg1, u16 *, 2) - 0x20)) << 0xE);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - ((s16) M2C_FIELD(arg1, u16 *, 6) - 0x20)) << 0xE);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            M2C_FIELD(arg0, u8 *, 0x9B) = 0x10U;
            return;
        }
        break;
    case 16:                                        /* switch 1 */
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80156F00) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156F00;
                func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156F00), 0);
            }
            if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801530F4;
                func_800A4ACC(arg3);
                if ((s8) M2C_FIELD(arg3, u8 *, 0x6D) > 0) {
                    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                }
                M2C_FIELD(arg3, s8 *, 0x73) = 0;
                M2C_FIELD(arg3, s8 *, 0x72) = 0;
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                func_800A56E0(0xB4);
            }
        }
        break;
    }
}
