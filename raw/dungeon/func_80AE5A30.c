#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
s32 func_8003F270();                                /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, void *, void *); /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *);       /* extern */
M2C_UNK func_80153728();                            /* static */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80156DEC;
extern u8 D_80156E34;
static M2C_UNK RO_80153020;                         /* unable to generate initializer: unknown type; const */

void func_80155230(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp18;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s3;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 *var_s0;
    u8 temp_v1;
    void *temp_a1;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0_3;
    void *temp_v1_3;
    void *temp_v1_4;
    void *var_a2;
    void *var_a3;
    void *var_v0;

    var_s3 = 0;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            switch (temp_v0) {                      /* switch 2 */
            case 7:                                 /* switch 2 */
                var_s3 = 1;
                goto block_13;
            case 6:                                 /* switch 2 */
                var_s3 = 1;
                goto block_14;
            case 5:                                 /* switch 2 */
                var_s3 = 1;
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
            if (var_s3 != 0) {
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
            if (func_800A94A0(arg3, var_s0, var_s3, arg0 + 0x98) != 0) {
                M2C_FIELD(arg0, u16 *, 0x96) = 0x11U;
block_51:
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
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
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80153728;
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
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        func_800A56E0(0x703);
    case 2:                                         /* switch 1 */
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if (((s16) temp_v0_2 == 0xB) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            temp_v0_3 = func_8003FD64(0x112, &D_80083498);
            temp_v1_4 = temp_v0_3 + 0x20;
            if (temp_v0_3 != NULL) {
                M2C_FIELD(temp_v1_4, s16 *, 0x96) = 9;
                M2C_FIELD(temp_v0_3, M2C_UNK **, 0x10) = &RO_80153020;
                M2C_FIELD(temp_v1_4, void **, 0xA8) = arg1;
                var_a3 = arg2;
                M2C_FIELD(temp_v1_4, u16 *, 0x94) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
                temp_s0 = M2C_FIELD(temp_v0_3, void **, 0xC);
                var_a2 = temp_s0;
                do {
                    M2C_FIELD(var_a2, s32 *, 0) = (s32) M2C_FIELD(var_a3, s32 *, 0);
                    M2C_FIELD(var_a2, s32 *, 4) = (s32) M2C_FIELD(var_a3, s32 *, 4);
                    M2C_FIELD(var_a2, s32 *, 8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
                    M2C_FIELD(var_a2, s32 *, 0xC) = (s32) M2C_FIELD(var_a3, s32 *, 0xC);
                    var_a3 += 0x10;
                    var_a2 += 0x10;
                } while (var_a3 != (arg2 + 0x30));
                M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
                M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
                M2C_FIELD(temp_s0, s8 *, 0xE) = 0x80;
                M2C_FIELD(temp_s0, s8 *, 0xD) = 0x80;
                M2C_FIELD(temp_s0, s8 *, 0xC) = 0x80;
                func_8004491C(temp_v0_3, &D_80045340, var_a2, var_a3);
                M2C_FIELD(temp_s0, u8 **, 0x2C) = &D_80156E34;
                func_80047784(temp_s0, D_80156E34, 0);
                M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
                M2C_FIELD(temp_s0, s16 *, 0x12) = 0xFF80;
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                temp_a1 = M2C_FIELD((arg0 - 0x20), void **, 0xC);
                temp_s0_2 = M2C_FIELD(temp_v0_3, void **, 8);
                if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp18, 1) != 0) {
                    M2C_FIELD(temp_s0_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
                    M2C_FIELD(temp_s0_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
                    M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
                    M2C_FIELD(temp_s0_2, u16 *, 2) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 2) + sp18);
                    M2C_FIELD(temp_s0_2, u16 *, 6) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 6) + sp1A);
                    M2C_FIELD(temp_s0_2, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0xA) + sp1C);
                }
            }
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0xB) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        }
        if (((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            goto block_51;
        }
        break;
    case 3:                                         /* switch 1 */
        if (((M2C_FIELD(arg2, s8 *, 4) == 3) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            M2C_FIELD(arg0, u16 *, 0x96) = 0x14U;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x100);
            M2C_FIELD(arg0, u16 *, 0xAC) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
            M2C_FIELD(arg2, u16 *, 0x12) = 0x7E80U;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        case 4:                                     /* switch 1 */
        }
        if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        }
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if ((temp_v0_4 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x12) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFEFF);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 0xAC);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFEFF);
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 0xAC);
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80156DEC) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156DEC;
                func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156DEC), 0);
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            }
            if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80153728;
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
