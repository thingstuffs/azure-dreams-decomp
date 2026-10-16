#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(void *, s32);                     /* extern */
s8 func_8009FB34(u8, u8);                           /* extern */
s32 func_8009FD7C(u8, u8, u8, u8);                  /* extern */
s16 func_800A0818(u8, u8, u8, u8, M2C_UNK *);       /* extern */
s32 func_800A1C58(void *);                          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AA79C(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA924(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AAB10(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AAF00(void *, M2C_UNK, void *, M2C_UNK *, void (*)(void *, M2C_UNK, void *, void *)); /* extern */
M2C_UNK func_8015424C();                            /* static */
M2C_UNK func_80154490(void *, M2C_UNK, void *, void *); /* static */
s32 func_80154C44(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_80154E08(void *, M2C_UNK, void *, void *); /* static */
s32 func_80154F20(void *, M2C_UNK, void *, M2C_UNK); /* static */
M2C_UNK func_80156650(void *, M2C_UNK, void *, void *); /* static */
M2C_UNK func_80156824(void *, M2C_UNK, void *, void *); /* static */
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern M2C_UNK D_800E2970;
extern M2C_UNK D_80156EB8;
extern M2C_UNK D_80156EC0;
extern M2C_UNK D_80156EF0;
extern M2C_UNK D_80156EF8;
extern M2C_UNK D_80156F00;

void func_80153CE8(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    M2C_UNK *var_a1;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    u16 temp_v0_2;

    if (D_80083462 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
        func_8015424C();
        return;
    }
    if (M2C_FIELD(arg3, u8 *, 0x25) == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80156F00) {
            var_a1 = &D_80156EF8;
            goto block_51;
        }
    } else if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200) {
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80156F00) {
            M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
            M2C_FIELD(arg0, s8 *, 0x9B) = 1;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, &D_80156EF8) == 0) {
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
                if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80156EB8) {
                    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80156EB8;
                    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80156EB8), 0);
                }
                M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
            }
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
            if ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, &D_80156EC0) == 0)) {
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
                    func_800AA888(arg0, arg1, arg2, arg3);
                    func_80156650(arg0, arg1, arg2, arg3);
                    return;
                }
                if ((func_800A1C58(arg3) << 0x10) != 0) {
                    func_800AAB10(arg0, arg1, arg2, arg3);
                }
                goto block_22;
            }
        } else {
block_22:
            temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
            if (M2C_FIELD(arg3, s8 *, 0x6D) > 0) {
                if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x20)) {
                    if ((u16) M2C_FIELD(arg2, u8 *, 0x24) != D_80082EA4) {
                        if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                            if ((!(D_80083462 & 0x2000) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0)) && ((func_80154F20(arg0, arg1, arg2, 0) << 0x10) != 0)) {
                                temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
                                M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
                                if (temp_v0_2 & 0x8000) {
                                    goto block_30;
                                }
                                goto block_40;
                            }
                        } else {
block_30:
                            temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
                            switch (temp_v0_3) {
                            case 8:
                                if ((func_80154C44(arg0, arg1, arg2, arg3) << 0x10) == 0) {
                                    func_80154E08(arg0, arg1, arg2, arg3);
                                    return;
                                }
                                break;
                            case 9:
                                func_80156824(arg0, arg1, arg2, arg3);
                                return;
                            case 5:
                            case 6:
                            case 7:
                                M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &sp18);
                                if (M2C_FIELD(D_800814A8, u8 *, 0x9A) != 0x11) {
                                    goto block_36;
                                }
block_38:
                                func_800AAF00(arg0, arg1, arg2, &D_80156EF0, func_80153CE8);
                                return;
                            case 1:
                            case 2:
                            case 3:
                                goto block_38;
                            default:
                                goto block_40;
                            }
                        }
                    } else {
block_40:
                        func_80154490(arg0, arg1, arg2, arg3);
                    }
                } else {
                case 12:
block_36:
                    func_800A9A0C(arg3);
                }
            } else {
                temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
                if (!(temp_a1 & 0x2000) && ((temp_v0 < 0) || !(M2C_FIELD(((temp_v0 * 0x14) + &D_800E2970), u16 *, 0xC) & 2)) && !(temp_a1 & 0x430)) {
                    if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25)) << 0x10) != 0) {
                        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &sp18);
                    }
                }
                if (!(D_80083462 & 0x2000) && !(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    var_a1 = &D_80156EB8;
                    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80156EB8) {
block_51:
                        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
                        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
                    }
                }
            }
        }
    }
}
