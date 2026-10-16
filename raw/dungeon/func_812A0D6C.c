#include "common.h"
#include "m2c_compat.h"

s32 func_8003EE70();                                /* extern */
M2C_UNK func_80047320(void *, u8, M2C_UNK);         /* extern */
void *func_8009F394(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A17D4(void *, u8, u8);              /* extern */
M2C_UNK func_800A3784(void *);                      /* extern */
M2C_UNK func_800A4398(M2C_UNK);                     /* extern */
s32 func_800A8158(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_8014BE18(void *, void *, void *, void *); /* static */
M2C_UNK func_8014C514();                            /* static */
extern M2C_UNK D_8006CC74;
extern void *D_800803DC;
extern s16 D_800848E0;
extern M2C_UNK D_80085990;
extern s32 D_8008599C;
extern M2C_UNK D_8014EE8C;
extern M2C_UNK D_8014EEDC;

void func_8014D56C(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s5;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u8 *var_s1;
    u8 temp_v1;
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
                var_s1 = NULL;
                break;
            }
        } else {
            temp_v1_2 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            if (temp_v1_2 != 2) {
                if (temp_v1_2 < 3) {
                    var_s1 = NULL;
                    if (temp_v1_2 != 1) {

                    } else {
                    case 1:                         /* switch 2 */
block_15:
                        var_s1 = arg3 + 8;
                    }
                } else {
                    var_s1 = NULL;
                    if (temp_v1_2 == 3) {
                    case 3:                         /* switch 2 */
block_13:
                        var_s1 = arg3 + 0xE;
                    }
                }
            } else {
            case 2:                                 /* switch 2 */
block_14:
                var_s1 = arg3 + 0xB;
            }
        }
        if (*var_s1 != 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
            if (var_s5 != 0) {
                var_v0 = D_800803DC;
                M2C_FIELD(arg3, void **, 0x60) = var_v0;
                goto block_22;
            }
            if (M2C_FIELD(((*var_s1 * 0x14) + &D_8006CC74), u8 *, 0x12) == 2) {
                var_v0 = M2C_FIELD(arg3, void **, 0x60);
                if (var_v0 != NULL) {
block_22:
                    temp_v1_3 = M2C_FIELD(var_v0, void **, -0x14);
                    M2C_FIELD(arg3, s8 *, 0x72) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x24);
                    M2C_FIELD(arg3, s8 *, 0x73) = (s8) M2C_FIELD(temp_v1_3, u8 *, 0x25);
                }
            } else {
                M2C_FIELD(arg3, void **, 0x60) = func_8009F394(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A), 0x10);
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
            if (func_800A8158(arg3, var_s1, var_s5, arg0 + 0x98) != 0) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg1, s32 *, 0x10) = 0;
                M2C_FIELD(arg1, s32 *, 0xC) = 0;
                return;
            }
        default:                                    /* switch 1 */
            return;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A17D4(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        D_8008599C = 0;
        M2C_FIELD(D_800803DC, u16 *, 0xA6) = (u16) (M2C_FIELD(D_800803DC, u16 *, 0xA6) - 1);
        func_800A3784(arg3);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8014C514;
        M2C_FIELD(arg3, s8 *, 0x73) = 0;
        M2C_FIELD(arg3, s8 *, 0x72) = 0;
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (func_8003EE70() != 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        func_800A4398(0x703);
    case 2:                                         /* switch 1 */
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_2 + 1);
        if (((s16) temp_v0_2 >= 8) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
block_45:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 3:                                         /* switch 1 */
        if ((M2C_FIELD(arg0, s16 *, 0xA2) == 0) || (temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96), M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_3 + 1), (((s16) temp_v0_3 < 0xF) == 0)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800A4398(0x703);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8014EEDC;
            func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8014EEDC), 0);
            return;
        }
        break;
    case 4:                                         /* switch 1 */
        func_8014BE18(arg0, arg1, arg2, arg3);
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_4 + 1);
        if (((s16) temp_v0_4 >= 3) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            goto block_45;
        }
        break;
    case 5:                                         /* switch 1 */
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_5 + 1);
        if (((s16) temp_v0_5 >= 0xA) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            return;
        }
        break;
    case 6:                                         /* switch 1 */
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 7:                                         /* switch 1 */
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A17D4(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8014EE8C) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8014EE8C;
                func_80047320(arg2, *((((s32) (D_800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8014EE8C), 0);
                M2C_FIELD(arg0, s16 *, 0x9E) = 0;
                M2C_FIELD(arg0, s16 *, 0x92) = -0x20;
                return;
            }
        }
        break;
    case 8:                                         /* switch 1 */
        if (M2C_FIELD(&D_80085990, s32 *, 0xC) == 0) {
            M2C_FIELD(&D_80085990, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80085990, u16 *, 0xA) - 1);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8014C514;
            func_800A3784(arg3);
            M2C_FIELD(arg3, s8 *, 0x73) = 0;
            M2C_FIELD(arg3, s8 *, 0x72) = 0;
            M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            func_800A4398(0xB4);
        }
        break;
    }
}
