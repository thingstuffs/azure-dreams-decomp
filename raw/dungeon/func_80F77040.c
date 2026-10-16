#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, u16 *, M2C_UNK);     /* extern */
s32 func_8003F270(s16 *, M2C_UNK);                  /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
void *func_800A05A4(void *, u8, u8, s16, s32);      /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
s32 func_800A6D30(s32);                             /* extern */
s32 func_800A94A0(void *, u8 *, s32, void *, u16, u16, u16); /* extern */
M2C_UNK func_80158E68();                            /* static */
M2C_UNK func_8015BEC0();                            /* static */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8006DE24;
extern void *D_800814A8;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEA68;
extern M2C_UNK D_8015C194;

void func_8015A840(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp20;
    u16 sp22;
    u16 sp24;
    s32 sp28;
    s16 *temp_a0_2;
    s16 temp_fp;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s1;
    s32 var_s2;
    s8 var_v0_2;
    s8 var_v1;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u8 *var_s0;
    u8 temp_v1;
    void *temp_a1;
    void *temp_s0;
    void *temp_v0_3;
    void *temp_v1_3;
    void *var_v0;

    temp_a0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_a0_2 = temp_a0 + &D_8006CCE8;
    sp28 = (s32) *(temp_a0 + &D_8006CCD8);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_fp = *temp_a0_2;
    var_s1 = 0;
    switch (temp_v1) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            temp_v0 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
            switch (temp_v0) {                      /* switch 2 */
            case 7:                                 /* switch 2 */
                var_s1 = 1;
                goto block_17;
            case 6:                                 /* switch 2 */
                var_s1 = 1;
                goto block_18;
            case 5:                                 /* switch 2 */
                var_s1 = 1;
                goto block_19;
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
block_19:
                        var_s0 = arg3 + 8;
                    }
                } else {
                    var_s0 = NULL;
                    if (temp_v1_2 == 3) {
                    case 3:                         /* switch 2 */
block_17:
                        var_s0 = arg3 + 0xE;
                    }
                }
            } else {
            case 2:                                 /* switch 2 */
block_18:
                var_s0 = arg3 + 0xB;
            }
        }
        if (*var_s0 != 0) {
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFF7F);
            if (var_s1 != 0) {
                var_v0 = D_800814A8;
                M2C_FIELD(arg3, void **, 0x60) = var_v0;
                goto block_26;
            }
            if (M2C_FIELD(((*var_s0 * 0x14) + &D_8006DE24), u8 *, 0x12) == 2) {
                var_v0 = M2C_FIELD(arg3, void **, 0x60);
                if (var_v0 != NULL) {
block_26:
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
            if (func_800A94A0(arg3, var_s0, var_s1, arg0 + 0x98, M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, u16 *, 0xA)) != 0) {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                func_800A56E0(0x703);
                M2C_FIELD(arg0, u16 *, 0xA8) = -1U;
                M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
                return;
            }
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
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80158E68;
        M2C_FIELD(arg3, s8 *, 0x73) = 0;
        M2C_FIELD(arg3, s8 *, 0x72) = 0;
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (func_8003F270(temp_a0_2, 1) != 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 2:                                         /* switch 1 */
        if ((M2C_FIELD(arg2, s8 *, 4) == 1) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) {
            M2C_FIELD(arg0, u16 *, 0xA8) = 4U;
        }
        if (((u32) ((u8) M2C_FIELD(arg2, s8 *, 4) - 1) < 2U) && (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8015C194)) {
            if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, &sp20, 1) == 0) {
                sp24 = 0;
                sp22 = 0;
                sp20 = 0;
            }
            temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA8) - 1;
            M2C_FIELD(arg0, u16 *, 0xA8) = temp_v0_2;
            if (!(temp_v0_2 & 0x8000)) {
                var_s2 = 9;
                do {
                    temp_v0_3 = func_8003FD64(0x312, &D_80083498);
                    if (temp_v0_3 != NULL) {
                        func_8004491C(temp_v0_3, &D_80045340);
                        temp_s0 = M2C_FIELD(temp_v0_3, void **, 0xC);
                        M2C_FIELD(temp_v0_3, M2C_UNK (**)(), 0x10) = func_8015BEC0;
                        temp_a0_3 = sp28 << 6;
                        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s16 *, 2) = (s16) ((M2C_FIELD(arg1, u16 *, 2) + sp20 + temp_a0_3 + (func_800A6D30() & 0x3F)) - 0x1F);
                        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s16 *, 6) = (s16) ((M2C_FIELD(arg1, u16 *, 6) + sp22 + (temp_fp << 6) + (func_800A6D30(temp_a0_3) & 0x3F)) - 0x1F);
                        M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
                        temp_a1 = temp_v0_3 + 0x20;
                        M2C_FIELD(temp_a1, s16 *, 0xC) = (s16) (M2C_FIELD(arg1, u16 *, 2) + sp20);
                        M2C_FIELD(temp_a1, s16 *, 0xE) = (s16) (M2C_FIELD(arg1, u16 *, 6) + sp22);
                        M2C_FIELD(temp_a1, s16 *, 0x48) = 4;
                        M2C_FIELD(temp_a1, s16 *, 0x10) = (s16) (M2C_FIELD(arg1, u16 *, 0xA) + sp24);
                        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x600;
                        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x600;
                        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
                        M2C_FIELD(temp_s0, M2C_UNK **, 0) = &D_800DEA68;
                        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                        M2C_FIELD(temp_s0, s8 *, 4) = 0;
                        M2C_FIELD(temp_s0, s8 *, 5) = 0;
                        M2C_FIELD(temp_s0, s32 *, 0xC) = 0x707070;
                        M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(&D_800DEA68, s32 *, 4);
                        M2C_FIELD(temp_a1, s16 *, 0x4C) = 0;
                    }
                    var_s2 -= 1;
                } while (var_s2 >= 0);
            }
        }
        if (((M2C_FIELD(arg2, s8 *, 4) == 6) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            M2C_FIELD(arg0, u16 *, 0x96) = 3U;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x80);
        }
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if ((temp_v0_4 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8015C194) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015C194;
                func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015C194), 0);
            }
            if (M2C_FIELD(&D_80083460, s32 *, 0xC) == 0) {
                M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
                M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80158E68;
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
