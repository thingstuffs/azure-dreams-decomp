#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047738(void *, u8, s8);              /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
s32 func_800644B8(s32);                             /* extern */
M2C_UNK func_800A020C(s32, void *);                 /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
extern M2C_UNK D_8006CCF8;
extern M2C_UNK D_801533A8;
extern M2C_UNK D_80156494;
extern M2C_UNK D_8015649C;
extern M2C_UNK D_80156504;

void func_80152BB8(void *arg0, void *arg1, void *arg2) {
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    M2C_UNK *temp_v1_5;
    M2C_UNK *temp_v1_9;
    M2C_UNK *var_a1;
    M2C_UNK *var_a1_2;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_s3;
    s16 temp_v0_3;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s16 var_v0_3;
    s32 temp_v0_2;
    s32 temp_v0_7;
    s32 temp_v1_11;
    s32 temp_v1_3;
    s32 temp_v1_7;
    s32 var_s6;
    s8 temp_s0;
    u16 temp_v0_4;
    u16 temp_v1_10;
    u16 temp_v1_2;
    u16 temp_v1_4;
    u16 temp_v1_6;
    u16 temp_v1_8;
    u16 var_v0;
    u16 var_v0_2;

    var_s6 = 0;
    if (*(u16 *)0x80083462 & 0x2000) {
        temp_v1 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1 == &D_801533A8) {
            temp_v1(arg0);
            return;
        }
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) & 0x7F);
        return;
    }
    temp_s0 = (s8) M2C_FIELD(arg0, u8 *, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) == 0) {
        temp_v0 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v0 != NULL) {
            temp_v0(arg0, arg1, arg2, arg0);
        }
        *((M2C_FIELD(arg0, u8 *, 0x9A) * 4) + &D_80156504)(arg0, arg1, arg2, arg0);
        if ((s16) temp_s0 != (s8) M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x40000) && !(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, s8 *, 0x9D) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1);
        } else {
            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_2 & 0x8000)) {
            temp_s3 = ((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7;
            if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s3) {
                func_80047738(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + temp_s3), M2C_FIELD(arg2, s8 *, 4));
                M2C_FIELD(arg0, s16 *, 0x94) = temp_s3;
            }
            if (*(temp_s3 + &D_8006CCF8) != 0) {
                var_v0 = M2C_FIELD(arg2, u16 *, 0x14) | 1;
            } else {
                var_v0 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0;
            if (M2C_FIELD(arg0, u8 *, 0x9A) != 8) {
                func_800A020C(M2C_FIELD(arg0, s32 *, 0x1C), arg2 + 0xC);
            }
            if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
                }
            } else {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xFFFBFFFF);
            }
            temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF;
            M2C_FIELD(arg0, s32 *, 0x1C) = temp_v1_3;
            if (temp_v1_3 & 0x40000) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    temp_v1_4 = M2C_FIELD(arg0, u16 *, 0x98);
                    if (temp_v1_4 & 0x8000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v1_4 & 0x7FFF);
                        temp_v1_5 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
                        var_a1 = &D_8015649C;
                        if (temp_v1_5 == &D_8015649C) {
                            var_a1 = &D_80156494;
                            goto block_31;
                        }
                        if (temp_v1_5 == &D_80156494) {
block_31:
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
                            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1), 0);
                        }
                    }
                    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
                        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80156494) {
                            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                        }
                    }
                    temp_v0_2 = func_800644B8((M2C_FIELD(arg0, s16 *, 0xA8) << 0xC) / 21);
                    var_s6 = temp_v0_2 >> 8;
                    if (M2C_FIELD(arg0, u8 *, 0x9A) == 0x12) {
                        var_s6 = temp_v0_2 >> 0xA;
                    }
                    M2C_FIELD(arg0, s16 *, 0xA8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA8) + 1);
                }
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                    temp_a0 = M2C_FIELD(arg0, s16 *, 0x92);
                    temp_v0_3 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) - M2C_FIELD(arg0, u16 *, 0x88);
                    temp_v1_6 = (u16) M2C_FIELD(arg0, s16 *, 0x92);
                    if ((temp_v0_3 - 0x30) < temp_a0) {
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_6 - 8);
                    } else if (temp_a0 < (temp_v0_3 - 0x3A)) {
                        M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v1_6 + 8);
                    }
                }
            } else {
                temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x98);
                M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v0_4 & 0x7FFF);
                if (!(temp_v0_4 & 8)) {
                    temp_v0_5 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) - (s16) M2C_FIELD(arg0, u16 *, 0x88);
                    if (temp_v0_5 < M2C_FIELD(arg0, s16 *, 0x92)) {
                        M2C_FIELD(arg0, s16 *, 0x92) = temp_v0_5;
                        M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                        M2C_FIELD(arg1, s32 *, 0x14) = 0;
                        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
                    }
                }
            }
        } else {
            var_v0_2 = temp_v1_2 & 0x8FFF;
            if (!(temp_v1_2 & 0x800)) {
                var_v0_2 = temp_v1_2 | 0x7000;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0_2;
            temp_v1_7 = M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF;
            M2C_FIELD(arg0, s32 *, 0x1C) = temp_v1_7;
            if (!(temp_v1_7 & 0x40000)) {
                M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                var_s6 = 0;
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) - 0);
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8)) {
                    temp_v0_6 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) - (s16) M2C_FIELD(arg0, u16 *, 0x88);
                    if (temp_v0_6 < M2C_FIELD(arg0, s16 *, 0x92)) {
                        M2C_FIELD(arg0, s16 *, 0x92) = temp_v0_6;
                        M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                        M2C_FIELD(arg1, s32 *, 0x14) = 0;
                        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
                    }
                }
            } else {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    temp_v1_8 = M2C_FIELD(arg0, u16 *, 0x98);
                    if (temp_v1_8 & 0x8000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (temp_v1_8 & 0x7FFF);
                        temp_v1_9 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
                        var_a1_2 = &D_8015649C;
                        if (temp_v1_9 == &D_8015649C) {
                            var_a1_2 = &D_80156494;
                            goto block_57;
                        }
                        if (temp_v1_9 == &D_80156494) {
block_57:
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1_2;
                            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + var_a1_2), 0);
                        }
                    }
                    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
                        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
                        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80156494) {
                            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
                        }
                    }
                    temp_v0_7 = func_800644B8((M2C_FIELD(arg0, s16 *, 0xA8) << 0xC) / 21);
                    var_s6 = temp_v0_7 >> 8;
                    if (M2C_FIELD(arg0, u8 *, 0x9A) == 0x12) {
                        var_s6 = temp_v0_7 >> 0xA;
                    }
                    M2C_FIELD(arg0, s16 *, 0xA8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA8) + 1);
                }
                if (!(M2C_FIELD(arg0, u16 *, 0x98) & 8) && ((temp_a0_2 = M2C_FIELD(arg0, s16 *, 0x92), temp_v0_8 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) - M2C_FIELD(arg0, u16 *, 0x88), temp_v1_10 = (u16) M2C_FIELD(arg0, s16 *, 0x92), var_v0_3 = temp_v1_10 - 8, (((temp_v0_8 - 0x30) < temp_a0_2) != 0)) || (var_v0_3 = temp_v1_10 + 8, ((temp_a0_2 < (temp_v0_8 - 0x3A)) != 0)))) {
                    M2C_FIELD(arg0, s16 *, 0x92) = var_v0_3;
                }
            }
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0x7FFF);
        }
        temp_v1_11 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_v1_11 & 0x40000000) {
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v1_11 & 0xBFFFFFFF);
            temp_v0_9 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20));
            if (temp_v0_9 < 0x200) {
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg0, u16 *, 0x88) - temp_v0_9));
                M2C_FIELD(arg0, u16 *, 0x88) = (u16) temp_v0_9;
            }
        }
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92) + var_s6);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
}
