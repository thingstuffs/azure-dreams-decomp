#include "common.h"
#include "m2c_compat.h"

s32 func_8009A180(void *, s32);                     /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
s32 func_8009A540(s32, u8, u8, s16);                /* extern */
s32 func_8009A66C(s16, void *, void *, M2C_UNK);    /* extern */
s32 func_8009FD7C(u8, u8, u8, u8);                  /* extern */
s16 func_800A0134(void *, void *);                  /* extern */
void *func_800A02AC(void *, u8, u8);                /* extern */
void *func_800A04F0(void *, u8, u8, s16);           /* extern */
u16 func_800A0818(u8, u8, u8, u8, s32);             /* extern */
M2C_UNK func_800A0E6C(void *, s8, void *, void *);  /* extern */
M2C_UNK func_800A19E4(void *, void *, M2C_UNK, M2C_UNK, s32); /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6E8C(void *, M2C_UNK, s16 *, s16 *);   /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
s32 func_80165EBC(void *, void *, void *);          /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8006CD00;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800E2970;

void func_801655F4(void *arg0, void *arg2, void *arg3) {
    s16 sp18;
    s16 sp1A;
    M2C_UNK var_a2_2;
    M2C_UNK var_a2_3;
    s16 temp_a1;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_8;
    s16 temp_v1_3;
    s16 var_a2;
    s16 var_s0;
    s16 var_s3;
    s16 var_v0_6;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_s3;
    s32 temp_v0_3;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s6;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s8 temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_6;

    var_s6 = 0;
    if ((M2C_FIELD(&D_80083460, u16 *, 2) & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        if (((u8) M2C_FIELD(arg3, u8 *, 0x12) >= 2U) || ((func_80165EBC(arg0, arg2, arg3) << 0x10) == 0)) {
            func_800A9A0C(arg3);
            return;
        }
        if (M2C_FIELD(&D_80083460, s32 *, 0xC) == arg3) {
            M2C_FIELD(arg3, u16 *, 0x46) = 0xC008U;
        }
    } else if (M2C_FIELD(&D_80083460, u16 *, 2) & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_800A02AC(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                if (temp_v0 != NULL) {
                    temp_v0_2 = M2C_FIELD(temp_v0, void **, -0x14);
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_v0_2, u8 *, 0x24), M2C_FIELD(temp_v0_2, u8 *, 0x25), arg0 + 0x98);
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    return;
                }
                temp_v0_3 = M2C_FIELD(arg3, s32 *, 0x14);
                if (temp_v0_3 >= 0) {
                    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0_3 | 0x80000000);
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
                }
                goto block_55;
            }
            var_s3 = 0;
            if (func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A)) != NULL) {
                goto block_75;
            }
            goto block_56;
        }
        if (temp_v1 & 0x2000) {
            var_s3 = 0;
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                if (temp_v1 & 0x20000) {
                    temp_v1_2 = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(*(void **)0x800814A8, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                    temp_v0_4 = M2C_FIELD(&D_80082E80, u8 *, 0x24) + *(temp_v1_2 + &D_8006CCD8);
                    temp_a1 = M2C_FIELD(&D_80082E80, u8 *, 0x25) + *(temp_v1_2 + &D_8006CCE8);
                    sp18 = temp_v0_4;
                    sp1A = temp_a1;
                    if ((M2C_FIELD(arg2, u8 *, 0x24) != (temp_v0_4 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_a1 & 0xFFFF))) {
                        temp_s0 = arg0 + 0x98;
                        temp_v0_5 = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (u8) sp18, (u8) sp1A, temp_s0);
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_5;
                        if ((func_8009A66C(temp_v0_5, arg2, arg3, 0x20) << 0x10) <= 0) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), temp_s0);
                        }
                        var_s3 = 0;
                        if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25)) << 0x10) != 0) {
                            var_s6 = 1;
                        }
                        goto block_56;
                    }
                    goto block_75;
                }
                goto block_54;
            }
            goto block_56;
        }
        temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
        temp_s3 = func_800A6E8C(arg2, 0x12, &sp18, &sp1A);
        if ((temp_a0 < 0) || !(M2C_FIELD(((temp_a0 * 0x14) + &D_800E2970), u16 *, 0xC) & 2)) {
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                temp_v0_6 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
                if ((temp_v0_6 == NULL) || !(M2C_FIELD(temp_v0_6, s32 *, 0x1C) & 0x2000) || (func_800A0134(temp_v0_6, arg3) >= 0x81) || ((func_8009A540(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) == 0)) {
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20000) {
                        M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), arg0 + 0x98);
                        if (((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25)) << 0x10) != 0) && (func_800A0134(*(void *)0x800814A8, arg3) < 0x81)) {
                            if ((func_8009A540(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) == 0) {
                                if ((temp_s3 << 0x10) != 0) {
                                    var_v0 = M2C_FIELD(arg2, u8 *, 0x24) - (u16) sp18;
                                    if (var_v0 < 0) {
                                        var_v0 = -var_v0;
                                    }
                                    if (var_v0 < 2) {
                                        var_v0_2 = M2C_FIELD(arg2, u8 *, 0x25) - (u16) sp1A;
                                        if (var_v0_2 < 0) {
                                            var_v0_2 = -var_v0_2;
                                        }
                                        if (var_v0_2 >= 2) {
                                            goto block_43;
                                        }
                                        goto block_53;
                                    }
block_43:
                                    var_a2 = (s16) (u16) sp18;
                                    goto block_52;
                                }
                                goto block_55;
                                goto block_56;
                            }
                            goto block_75;
                        }
                        goto block_55;
                    }
                    if ((temp_s3 << 0x10) != 0) {
                        var_v0_3 = M2C_FIELD(arg2, u8 *, 0x24) - (u16) sp18;
                        if (var_v0_3 < 0) {
                            var_v0_3 = -var_v0_3;
                        }
                        if (var_v0_3 < 2) {
                            var_v0_4 = M2C_FIELD(arg2, u8 *, 0x25) - (u16) sp1A;
                            if (var_v0_4 < 0) {
                                var_v0_4 = -var_v0_4;
                            }
                            if (var_v0_4 >= 2) {
                                goto block_51;
                            }
block_53:
                            var_s3 = 0;
                            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) ((func_800A6D30() & 7) << 9);
                        } else {
block_51:
                            var_a2 = (s16) (u16) sp18;
block_52:
                            var_s3 = 0;
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (u8) var_a2, (u8) sp1A);
                        }
                    } else {
                        goto block_54;
                    }
                    goto block_56;
                }
                goto block_75;
            }
            goto block_55;
        }
block_54:
        func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
block_55:
        var_s3 = 0;
block_56:
loop_57:
        temp_v1_3 = (s16) M2C_FIELD(arg3, u16 *, 0x2A);
        temp_v0_7 = var_s3 << 0x10;
        if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
            var_s0 = temp_v1_3 - *((temp_v0_7 >> 0xF) + &D_8006CD00);
        } else {
            var_s0 = temp_v1_3 + *((temp_v0_7 >> 0xF) + &D_8006CD00);
        }
        if ((func_8009A66C(var_s0, arg2, arg3, 0x20) << 0x10) > 0) {
            if ((var_s3 < 3) || (var_s6 == 0)) {
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) var_s0;
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) + 1);
                var_a2_2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2_2 = 0x300;
                }
                func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
                temp_a0_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a0_2 + &D_8006CCD8));
                M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a0_2 + &D_8006CCE8));
                var_a2_3 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2_3 = 0x300;
                }
                func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_3);
                var_v0_5 = var_s3 << 0x10;
                goto block_72;
            }
            goto block_75;
        }
        var_v0_6 = var_s3 + 1;
        if (((var_s3 << 0x10) != 0) || (var_v0_6 = var_s3 + 1, (*(u16 *)0x80082EA4 == (u16) M2C_FIELD(arg2, u8 *, 0x24))) || (var_v0_6 = var_s3 + 1, ((func_8009A180(arg3, M2C_FIELD(*(void *)0x800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
            var_s3 = var_v0_6;
            var_v0_5 = var_s3 << 0x10;
            if (var_v0_6 >= 8) {
block_72:
                if ((var_v0_5 >> 0x10) >= 8) {
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                    func_800A9A0C(arg3);
                    return;
                }
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg0, s8 *, 0x9C) = (s8) (u8) M2C_FIELD(arg2, s8 *, 0x26);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                M2C_FIELD(&D_80083460, u16 *, 8) = (u16) (M2C_FIELD(&D_80083460, u16 *, 8) + 1);
                if ((s8) M2C_FIELD(arg3, u8 *, 0x6D) == 0) {
block_75:
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    return;
                }
                temp_v0_8 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                if (temp_v0_8 < 0x200) {
                    M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_8;
                }
            } else {
                goto loop_57;
            }
        }
    }
}
