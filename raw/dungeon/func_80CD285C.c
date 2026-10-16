#include "common.h"
#include "m2c_compat.h"

s32 func_8009A180(void *, s32);                     /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
s32 func_8009A540(s32, u8, u8, s16);                /* extern */
s32 func_8009A66C(s16, void *, void *, M2C_UNK);    /* extern */
s32 func_8009FD40(void *, void *);                  /* extern */
s32 func_8009FD7C(u8, u8, u8, u8);                  /* extern */
s16 func_800A0134(void *, void *);                  /* extern */
void *func_800A02AC(void *, u8, u8);                /* extern */
void *func_800A04F0(void *, u8, u8, s16);           /* extern */
s32 func_800A07D0(u8, u8, u8, u8);                  /* extern */
u16 func_800A0818(u8, u8, u8, u8, void *);          /* extern */
M2C_UNK func_800A0E6C(void *, s8, void *, void *);  /* extern */
M2C_UNK func_800A19E4(void *, void *, M2C_UNK, M2C_UNK, s32); /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
s32 func_80162BCC(void *, void *, void *);          /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_8006CD00;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800E2970;

void func_8016205C(void *arg0, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_v0_4;
    s16 temp_v0_9;
    s16 var_s0;
    s16 var_s1;
    s16 var_v0_5;
    s16 var_v1;
    s32 temp_a0_3;
    s32 temp_s0_3;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s8 temp_a0;
    u16 temp_v1;
    u8 var_v0;
    void *temp_a0_2;
    void *temp_s0_2;
    void *temp_s1_2;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v0_8;

    temp_v1 = *(u16 *)0x80083462;
    if ((temp_v1 & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        if ((M2C_FIELD(arg3, s8 *, 0x71) >= 0) || ((func_80162BCC(arg0, arg2, arg3) << 0x10) == 0)) {
            func_800A9A0C(arg3);
            return;
        }
        M2C_FIELD(arg3, u16 *, 0x46) = 0xC008U;
        return;
    }
    if (temp_v1 & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_2 & 0x410) {
            if (temp_v1_2 & 0x400) {
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
                goto block_47;
            }
            var_s1 = 0;
            if (func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A)) != NULL) {
                goto block_72;
            }
            goto block_48;
        }
        if (temp_v1_2 & 0x2000) {
            var_s1 = 0;
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                if (temp_v1_2 & 0x20000) {
                    temp_v1_3 = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(*(void **)0x800814A8, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                    temp_s0 = M2C_FIELD(&D_80082E80, u8 *, 0x24) + *(temp_v1_3 + &D_8006CCD8);
                    temp_s1 = M2C_FIELD(&D_80082E80, u8 *, 0x25) + *(temp_v1_3 + &D_8006CCE8);
                    if ((M2C_FIELD(arg2, u8 *, 0x24) != (temp_s0 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_s1 & 0xFFFF))) {
                        temp_s0_2 = arg0 + 0x98;
                        temp_v0_4 = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (u8) temp_s0, (u8) temp_s1, temp_s0_2);
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_4;
                        var_s1 = 0;
                        if ((func_8009A66C(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), temp_s0_2);
                        }
                        goto block_48;
                    }
                    goto block_72;
                }
                goto block_24;
            }
            goto block_48;
        }
        temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
        if ((temp_a0 >= 0) && (M2C_FIELD(((temp_a0 * 0x14) + &D_800E2970), u16 *, 0xC) & 2)) {
block_24:
            func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
            var_s1 = 0;
            goto block_48;
        }
        if ((M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) || (temp_v0_5 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A)), (temp_v0_5 == NULL)) || !(M2C_FIELD(temp_v0_5, s32 *, 0x1C) & 0x2000) || (func_800A0134(temp_v0_5, arg3) >= 0x81) || ((func_8009A540(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) == 0)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20000) {
                M2C_FIELD(arg0, u8 *, 0xA6) = 0U;
                temp_v0_6 = *(void *)0x800814A8;
                temp_a0_2 = M2C_FIELD(temp_v0_6, void **, 0xAC);
                if ((temp_a0_2 == NULL) || (temp_v0_7 = M2C_FIELD(temp_v0_6, void **, 0xB0), (temp_v0_7 == NULL))) {
                    temp_v1_4 = (M2C_FIELD(*(void *)0x800814A8, u16 *, 0x2A) + func_800A07D0(M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25))) & 0xFFF;
                    var_v0 = 3;
                    if (((u32) (temp_v1_4 - 0x401) >= 0x7FFU) && ((temp_v1_4 == 0x400) || (var_v0 = 2, (temp_v1_4 == 0xC00)))) {
                        var_v0 = 1;
                    }
                    M2C_FIELD(arg3, u8 *, 0x45) = var_v0;
                    temp_v1_5 = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(*(void *)0x800814A8, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                    temp_a2 = M2C_FIELD(&D_80082E80, u8 *, 0x24) + *(temp_v1_5 + &D_8006CCD8);
                    temp_a3 = M2C_FIELD(&D_80082E80, u8 *, 0x25) + *(temp_v1_5 + &D_8006CCE8);
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (u8) temp_a2, (u8) temp_a3, arg0 + 0x98);
                    if (M2C_FIELD(arg2, u8 *, 0x24) == (temp_a2 & 0xFFFF)) {
                        var_s1 = 0;
                        if (M2C_FIELD(arg2, u8 *, 0x25) == (temp_a3 & 0xFFFF)) {
                            goto block_72;
                        }
                        goto block_48;
                    }
                    goto block_47;
                }
                temp_s2 = M2C_FIELD(temp_a0_2, void **, -0x14);
                temp_s1_2 = M2C_FIELD(temp_v0_7, void **, -0x14);
                temp_s0_3 = func_8009FD40(temp_s2, arg2);
                temp_v0_8 = arg0 + 0x98;
                if ((temp_s0_3 << 0x10) < (func_8009FD40(temp_s1_2, arg2) << 0x10)) {
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_s2, u8 *, 0x24), M2C_FIELD(temp_s2, u8 *, 0x25), temp_v0_8);
                    var_s1 = 0;
                    if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_s2, u8 *, 0x24), M2C_FIELD(temp_s2, u8 *, 0x25)) << 0x10) != 0) {
                        goto block_72;
                    }
                    goto block_48;
                }
                M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_s1_2, u8 *, 0x24), M2C_FIELD(temp_s1_2, u8 *, 0x25), temp_v0_8);
                var_s1 = 0;
                if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_s2, u8 *, 0x24), M2C_FIELD(temp_s2, u8 *, 0x25)) << 0x10) != 0) {
                    goto block_72;
                }
                goto block_48;
            }
            var_s1 = 0;
            if (M2C_FIELD(arg0, u8 *, 0xA6) == 0) {
                M2C_FIELD(arg0, u8 *, 0xA6) = 1U;
                M2C_FIELD(arg0, s16 *, 0xA4) = (s16) (((func_800A6D30() & 3) << 0xA) + 0x200);
block_47:
                var_s1 = 0;
            }
block_48:
loop_49:
            if (M2C_FIELD(arg0, u8 *, 0xA6) != 0) {
                var_v1 = M2C_FIELD(arg0, s16 *, 0xA4);
                var_v0_2 = var_s1 << 0x10;
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 2)) {
                    var_v0_3 = var_v0_2 >> 0xF;
                    goto block_55;
                }
                goto block_53;
            }
            var_v1 = (s16) M2C_FIELD(arg3, u16 *, 0x2A);
            var_v0_2 = var_s1 << 0x10;
            if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
block_53:
                var_s0 = var_v1 - *((var_v0_2 >> 0xF) + &D_8006CD00);
            } else {
                var_v0_3 = var_v0_2 >> 0xF;
block_55:
                var_s0 = var_v1 + *(var_v0_3 + &D_8006CD00);
            }
            if ((func_8009A66C(var_s0, arg2, arg3, 0x20) << 0x10) > 0) {
                if ((var_s1 < 3) || (((0 << 0x10) == 0) && (M2C_FIELD(arg0, u8 *, 0xA6) == 0))) {
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) var_s0;
                    M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                    M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) + 1);
                    var_a2 = 0x3000;
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                        var_a2 = 0x300;
                    }
                    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
                    temp_a0_3 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                    M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a0_3 + &D_8006CCD8));
                    M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a0_3 + &D_8006CCE8));
                    var_a2_2 = 0x3000;
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                        var_a2_2 = 0x300;
                    }
                    func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
                    var_v0_4 = var_s1 << 0x10;
                    goto block_69;
                }
                goto block_72;
            }
            var_v0_5 = var_s1 + 1;
            if (((var_s1 << 0x10) != 0) || (var_v0_5 = var_s1 + 1, (*(u16 *)0x80082EA4 == (u16) M2C_FIELD(arg2, u8 *, 0x24))) || (var_v0_5 = var_s1 + 1, ((func_8009A180(arg3, M2C_FIELD(*(void *)0x800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
                var_s1 = var_v0_5;
                var_v0_4 = var_s1 << 0x10;
                if (var_v0_5 >= 8) {
block_69:
                    if ((var_v0_4 >> 0x10) >= 8) {
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
                        goto block_72;
                    }
                    temp_v0_9 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                    if (temp_v0_9 < 0x200) {
                        M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_9;
                    }
                } else {
                    goto loop_49;
                }
            }
        } else {
block_72:
            M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
        }
    }
}
