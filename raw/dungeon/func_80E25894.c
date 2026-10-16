#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(void *, s32);                     /* extern */
s8 func_8009FB34(u8, u8);                           /* extern */
s32 func_8009FD7C(u8, u8, u8, u8);                  /* extern */
s16 func_800A0818(u8, u8, u8, u8, M2C_UNK *);       /* extern */
s32 func_800A1C58(void *);                          /* extern */
s32 func_800A6D30(void *);                          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AA79C(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA924(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AAB10(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AAF00(void *, M2C_UNK, void *, M2C_UNK *, void (*)(void *, M2C_UNK, void *, void *)); /* extern */
M2C_UNK func_801596D8();                            /* static */
M2C_UNK func_801598B4(void *, M2C_UNK, void *, void *); /* static */
s32 func_80159FFC(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_8015A1C0(void *, M2C_UNK, void *, void *); /* static */
s32 func_8015A438(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_8015A72C(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_8015A83C(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_8015A94C(void *, M2C_UNK, void *, void *); /* static */
s32 func_8015AA5C(void *, M2C_UNK, void *, M2C_UNK); /* static */
M2C_UNK func_8015C520(void *, M2C_UNK, void *, void *); /* static */
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern M2C_UNK D_800E2970;
extern M2C_UNK D_8015E460;
extern M2C_UNK D_8015E468;
extern M2C_UNK D_8015E470;
extern M2C_UNK D_8015E4A8;

void func_80159094(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s16 temp_v0_5;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s8 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_2;
    u16 var_v0;

    if (D_80083462 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
        func_801596D8();
        return;
    }
    if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8015E470) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E468;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E468), 0);
        }
    } else if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200) {
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_8015E470) {
            M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
            M2C_FIELD(arg0, s8 *, 0x9B) = 1;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, &D_8015E468) == 0) {
            goto block_9;
        }
    } else {
block_9:
        if (!(D_80083462 & 0x2000)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }
            if (M2C_FIELD(arg0, u8 *, 0x9A) != 0xE) {
                M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
            }
            if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_8015E460) {
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015E460;
                func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015E460), 0);
                M2C_FIELD(arg2, s8 *, 5) = 1;
                M2C_FIELD(arg0, u16 *, 0xA6) = 0U;
                M2C_FIELD(arg0, s16 *, 0xAC) = 0;
            }
            temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
            if (temp_v1 & 0x20) {
                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (temp_v1 & 0xFFFBFFFF);
                var_v0 = M2C_FIELD(arg0, u16 *, 0x98) | 8;
            } else {
                M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (temp_v1 | 0x40000);
                var_v0 = M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7;
            }
            M2C_FIELD(arg0, u16 *, 0x98) = var_v0;
            if ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, &D_8015E4A8) == 0)) {
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
                    func_800AA888(arg0, arg1, arg2, arg3);
                    temp_v1_2 = M2C_FIELD(arg0, u16 *, 0xA6);
                    M2C_FIELD(arg0, u16 *, 0xA6) = 0U;
                    M2C_FIELD(arg0, s16 *, 0xAC) = 0;
                    M2C_FIELD(arg0, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) - temp_v1_2);
                    func_8015C520(arg0, arg1, arg2, arg3);
                    return;
                }
                if ((func_800A1C58(arg3) << 0x10) != 0) {
                    func_800AAB10(arg0, arg1, arg2, arg3);
                }
                goto block_25;
            }
        } else {
block_25:
            temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
            if (M2C_FIELD(arg3, s8 *, 0x6D) > 0) {
                if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x20)) {
                    if ((u16) M2C_FIELD(arg2, u8 *, 0x24) != D_80082EA4) {
                        if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                            if ((!(D_80083462 & 0x2000) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0)) && ((func_8015AA5C(arg0, arg1, arg2, 0) << 0x10) != 0)) {
                                temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
                                M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
                                if (temp_v0_2 & 0x8000) {
                                    goto block_33;
                                }
                                goto block_50;
                            }
                        } else {
block_33:
                            temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
                            switch (temp_v0_3) {    /* switch 1 */
                            case 8:                 /* switch 1 */
                                if ((func_80159FFC(arg0, arg1, arg2, arg3) << 0x10) == 0) {
                                    func_8015A1C0(arg0, arg1, arg2, arg3);
                                    return;
                                }
                                break;
                            case 9:                 /* switch 1 */
                                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
                                    temp_v0_4 = M2C_FIELD(arg3, s32 *, 0x14);
                                    if (temp_v0_4 >= 0) {
                                        M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0_4 | 0x80000000);
                                        M2C_FIELD(arg3, s16 *, 0x2A) = (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x2A) + ((func_800A6D30(arg0) & 7) << 9));
                                    }
                                }
                                temp_v0_5 = func_8015A438(arg0, arg1, arg2, arg3) + 1;
                                switch (temp_v0_5) { /* switch 2 */
                                case 1:             /* switch 2 */
                                    func_8015A72C(arg0, arg1, arg2, arg3);
                                    return;
                                case 3:             /* switch 2 */
                                    func_8015A83C(arg0, arg1, arg2, arg3);
                                    return;
                                case 4:             /* switch 2 */
                                    func_8015A94C(arg0, arg1, arg2, arg3);
                                    return;
                                }
                                break;
                            case 5:                 /* switch 1 */
                            case 6:                 /* switch 1 */
                            case 7:                 /* switch 1 */
                                M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &sp18);
                                if (M2C_FIELD(D_800814A8, u8 *, 0x9A) != 0x11) {
                                    goto block_46;
                                }
block_48:
                                func_800AAF00(arg0, arg1, arg2, &D_8015E460, func_80159094);
                                return;
                            case 1:                 /* switch 1 */
                            case 2:                 /* switch 1 */
                            case 3:                 /* switch 1 */
                                goto block_48;
                            default:                /* switch 1 */
                                goto block_50;
                            }
                        }
                    } else {
block_50:
                        func_801598B4(arg0, arg1, arg2, arg3);
                    }
                } else {
                case 12:                            /* switch 1 */
block_46:
                    func_800A9A0C(arg3);
                }
            } else {
                temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
                if (!(temp_a1 & 0x2000) && ((temp_v0 < 0) || !(M2C_FIELD(((temp_v0 * 0x14) + &D_800E2970), u16 *, 0xC) & 2)) && !(temp_a1 & 0x430) && ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25)) << 0x10) != 0)) {
                    M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &sp18);
                }
            default:                                /* switch 2 */
            case 0:                                 /* switch 2 */
            case 2:                                 /* switch 2 */
            }
        }
    }
}
