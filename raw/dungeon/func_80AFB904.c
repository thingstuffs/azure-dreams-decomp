#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047738(void *, u8, s8);              /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800478B8(void *);                      /* extern */
M2C_UNK func_800A020C(s32, void *);                 /* extern */
s32 func_800A9E70(void *, void *, void *, void *);  /* extern */
M2C_UNK func_800AA36C(void *, void *, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
extern M2C_UNK D_8006CCF8;
extern M2C_UNK D_801657F4;
extern M2C_UNK D_80169988;
extern M2C_UNK D_801699A0;
extern M2C_UNK D_801699B0;
extern M2C_UNK D_801699B8;
extern M2C_UNK D_80169A1C;

void func_80165104(void *arg0, void *arg1, void *arg2) {
    M2C_UNK (*temp_v0)(void *, void *, void *, void *);
    M2C_UNK (*temp_v1)(void *, void *, void *, void *);
    M2C_UNK *temp_v0_6;
    M2C_UNK *temp_v1_2;
    s16 temp_a2;
    s16 temp_s0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s32 temp_v1_4;
    s32 var_v0;
    s8 temp_s0;
    u16 temp_v0_2;
    u16 temp_v1_3;
    u16 var_v0_2;
    u16 var_v0_3;

    if (*(u16 *)0x80083462 & 0x2000) {
        temp_v1 = M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, void *, void *), 0x8C);
        if (temp_v1 == &D_801657F4) {
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
        *((M2C_FIELD(arg0, u8 *, 0x9A) * 4) + &D_80169A1C)(arg0, arg1, arg2, arg0);
        var_v0 = temp_s0 << 0x10;
        if (M2C_FIELD(arg0, u8 *, 0x9A) == 0xE) {
            var_v0 = temp_s0 << 0x10;
            if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                var_v0 = temp_s0 << 0x10;
                if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x20)) {
                    temp_v1_2 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
                    if (temp_v1_2 != &D_80169988) {
                        if ((temp_v1_2 != &D_801699A0) && (temp_v1_2 != &D_801699B0) && (temp_v1_2 != &D_801699B8)) {
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80169988;
                            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80169988), 0);
                            M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
                            M2C_FIELD(arg0, s16 *, 0xA0) = 0xA;
                        }
                        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80169988) {
                            goto block_16;
                        }
                    } else {
block_16:
                        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x9E);
                        M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v0_2 + 1);
                        if ((s16) temp_v0_2 >= M2C_FIELD(arg0, s16 *, 0xA0)) {
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801699A0;
                            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801699A0), 0);
                            func_800478B8(arg2);
                            M2C_FIELD(arg0, s16 *, 0xA0) = 3;
                        }
                    }
                    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_801699A0) {
                        temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0xA0) - 1;
                        M2C_FIELD(arg0, s16 *, 0xA0) = temp_v0_3;
                        if (((temp_v0_3 << 0x10) <= 0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801699B0;
                            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801699B0), 0);
                            func_800478B8(arg2);
                            M2C_FIELD(arg0, s16 *, 0xA0) = 6;
                            M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + 0xFFE00000);
                            M2C_FIELD(arg1, s32 *, 0x14) = 0;
                            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
                        }
                    }
                    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_801699B0) {
                        temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0xA0) - 1;
                        M2C_FIELD(arg0, s16 *, 0xA0) = temp_v0_4;
                        if (((temp_v0_4 << 0x10) <= 0) && (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
                            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801699B8;
                            func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801699B8), 0);
                            func_800478B8(arg2);
                            M2C_FIELD(arg0, s16 *, 0xA0) = 3;
                        }
                    }
                    var_v0 = temp_s0 << 0x10;
                    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_801699B8) {
                        temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0xA0) - 1;
                        M2C_FIELD(arg0, s16 *, 0xA0) = temp_v0_5;
                        var_v0 = temp_s0 << 0x10;
                        if ((temp_v0_5 << 0x10) <= 0) {
                            if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
                                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80169988;
                                func_80047784(arg2, *((((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80169988), 0);
                                M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
                                M2C_FIELD(arg0, s16 *, 0xA0) = 0x14;
                            }
                            var_v0 = temp_s0 << 0x10;
                        }
                    }
                }
            }
        }
        if ((var_v0 >> 0x10) != (s8) M2C_FIELD(arg0, u8 *, 0x6D)) {
            func_800AA36C(arg0, arg1, arg2, arg0);
        }
        temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
        if (!(temp_v1_3 & 0x8000)) {
            temp_s0_2 = ((s32) (*(void *)0x80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7;
            if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s0_2) {
                temp_v0_6 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
                if (temp_v0_6 != NULL) {
                    func_80047738(arg2, *(temp_v0_6 + temp_s0_2), M2C_FIELD(arg2, s8 *, 4));
                }
                M2C_FIELD(arg0, s16 *, 0x94) = temp_s0_2;
            }
            if (*(temp_s0_2 + &D_8006CCF8) != 0) {
                var_v0_2 = M2C_FIELD(arg2, u16 *, 0x14) | 1;
            } else {
                var_v0_2 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0_2;
            if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 0x20)) {
                if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x40)) {
                    func_800478B8(arg2);
                }
            } else {
                M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x7000);
            }
            func_800A020C(M2C_FIELD(arg0, s32 *, 0x1C), arg2 + 0xC);
        } else {
            var_v0_3 = temp_v1_3 & 0x8FFF;
            if (!(temp_v1_3 & 0x800)) {
                var_v0_3 = temp_v1_3 | 0x7000;
            }
            M2C_FIELD(arg2, u16 *, 0x14) = var_v0_3;
        }
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
        if (M2C_FIELD(arg0, u16 *, 0x98) & 8) {
            M2C_FIELD(arg0, s8 *, 0x9D) = 0;
        } else {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + (M2C_FIELD(arg0, s8 *, 0x9D) * 0x14000));
            M2C_FIELD(arg0, s8 *, 0x9D) = (s8) ((u8) M2C_FIELD(arg0, s8 *, 0x9D) + 1);
        }
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg1, s32 *, 0x14));
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 4) && (temp_v0_7 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20)), ((temp_v0_7 < 0x200) != 0))) {
            temp_a2 = (s16) M2C_FIELD(arg0, u16 *, 0x88);
            if ((M2C_FIELD(arg0, s16 *, 0x92) + temp_a2) < temp_v0_7) {
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF);
            } else {
                if (temp_v0_7 >= temp_a2) {
                    M2C_FIELD(arg0, s32 *, 0x90) = 0;
                } else {
                    M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v0_7 - M2C_FIELD(arg0, u16 *, 0x88));
                }
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0x08000000);
                M2C_FIELD(arg0, s8 *, 0x9D) = 0;
            }
            temp_v1_4 = M2C_FIELD(arg0, s32 *, 0x1C);
            if (temp_v1_4 & 0x40000000) {
                M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (temp_v1_4 & 0xBFFFFFFF);
                temp_v0_8 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg0, u16 *, 0x88) - 0x20));
                M2C_FIELD(arg0, s16 *, 0x92) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x92) + (M2C_FIELD(arg0, u16 *, 0x88) - temp_v0_8));
                M2C_FIELD(arg0, u16 *, 0x88) = (u16) temp_v0_8;
            }
        } else {
            M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) & 0xF7FFFFFF);
        }
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0x88) + (u16) M2C_FIELD(arg0, s16 *, 0x92));
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x40);
    }
}
