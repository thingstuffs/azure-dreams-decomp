#include "common.h"
#include "m2c_compat.h"

s32 func_80098F70(void *, s32);                     /* extern */
M2C_UNK func_8009900C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800991C0(u8, u8, M2C_UNK);             /* extern */
s32 func_80099330(s32, u8, u8, s16);                /* extern */
s32 func_800996B0(s16, void *, void *, M2C_UNK);    /* extern */
s32 func_8009EB6C(u8, u8, u8, u8);                  /* extern */
s16 func_8009EF24(void *, void *);                  /* extern */
void *func_8009F09C(void *, u8, u8);                /* extern */
void *func_8009F2E0(void *, u8, u8, s16);           /* extern */
u16 func_8009F608(u8, u8, u8, u8, s32);             /* extern */
M2C_UNK func_8009FB34(void *, s8, void *, void *);  /* extern */
M2C_UNK func_800A06B4(void *, void *, M2C_UNK, M2C_UNK, s32); /* extern */
s32 func_800A59E8();                                /* extern */
M2C_UNK func_800A86C4(void *);                      /* extern */
s16 func_800BB784(s32, s32, s16);                   /* extern */
s32 func_8014D328(void *, void *, void *);          /* extern */
extern M2C_UNK D_8006BDA8;
extern M2C_UNK D_8006BDB8;
extern M2C_UNK D_8006BDD0;
extern M2C_UNK D_80081490;
extern M2C_UNK D_80085990;
extern M2C_UNK D_800E1D50;

void func_8014CBE0(void *arg0, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v0_4;
    s16 temp_v0_7;
    s16 temp_v1_3;
    s16 var_s0;
    s16 var_s1;
    s16 var_v0_2;
    s32 temp_a0_2;
    s32 temp_s0;
    s32 temp_v0_3;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s6;
    s32 var_v0;
    s8 temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_5;

    var_s6 = 0;
    if ((M2C_FIELD(&D_80085990, u16 *, 2) & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        if (((u8) M2C_FIELD(arg3, u8 *, 0x12) >= 2U) || ((func_8014D328(arg0, arg2, arg3) << 0x10) == 0)) {
            func_800A86C4(arg3);
            return;
        }
        if (M2C_FIELD(&D_80085990, s32 *, 0xC) == arg3) {
            M2C_FIELD(arg3, u16 *, 0x46) = 0xC008U;
        }
    } else if (M2C_FIELD(&D_80085990, u16 *, 2) & 0x2000) {
        func_800A06B4(arg2, arg3, 3, 6, arg0 + 0x9C);
        temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_8009F09C(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                if (temp_v0 != NULL) {
                    temp_v0_2 = M2C_FIELD(temp_v0, void **, -0x14);
                    M2C_FIELD(arg3, u16 *, 0x2A) = func_8009F608(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(temp_v0_2, u8 *, 0x24), M2C_FIELD(temp_v0_2, u8 *, 0x25), arg0 + 0x98);
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    return;
                }
                temp_v0_3 = M2C_FIELD(arg3, s32 *, 0x14);
                if (temp_v0_3 >= 0) {
                    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0_3 | 0x80000000);
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A59E8() & 7) << 9));
                }
                goto block_39;
            }
            var_s1 = 0;
            if (func_8009F2E0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A)) != NULL) {
                goto block_59;
            }
            goto block_40;
        }
        if (temp_v1 & 0x2000) {
            var_s1 = 0;
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                if (temp_v1 & 0x20000) {
                    temp_v1_2 = ((M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(*(void **)0x800803DC, u16 *, 0x2A) << 0x10) >> 0x19)) & 7) * 2;
                    temp_a2 = M2C_FIELD(&D_80081490, u8 *, 0x24) + *(temp_v1_2 + &D_8006BDA8);
                    temp_a1 = M2C_FIELD(&D_80081490, u8 *, 0x25) + *(temp_v1_2 + &D_8006BDB8);
                    if ((M2C_FIELD(arg2, u8 *, 0x24) != (temp_a2 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_a1 & 0xFFFF))) {
                        temp_s0 = arg0 + 0x98;
                        temp_v0_4 = func_8009F608(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (u8) temp_a2, (u8) temp_a1, temp_s0);
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_4;
                        if ((func_800996B0(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_8009F608(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25), temp_s0);
                        }
                        var_s1 = 0;
                        if ((func_8009EB6C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25)) << 0x10) != 0) {
                            var_s6 = 1;
                        }
                        goto block_40;
                    }
                    goto block_59;
                }
                goto block_37;
            }
            goto block_40;
        }
        temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
        if ((temp_a0 < 0) || !(M2C_FIELD(((temp_a0 * 0x14) + &D_800E1D50), u16 *, 0xC) & 2)) {
            var_s1 = 0;
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                temp_v0_5 = func_8009F2E0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) M2C_FIELD(arg3, u16 *, 0x2A));
                if ((temp_v0_5 == NULL) || !(M2C_FIELD(temp_v0_5, s32 *, 0x1C) & 0x2000) || (func_8009EF24(temp_v0_5, arg3) >= 0x81) || ((func_80099330(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) == 0)) {
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20000) {
                        M2C_FIELD(arg3, u16 *, 0x2A) = func_8009F608(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25), arg0 + 0x98);
                        if ((func_8009EB6C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(&D_80081490, u8 *, 0x24), M2C_FIELD(&D_80081490, u8 *, 0x25)) << 0x10) != 0) {
                            var_s1 = 0;
                            if (func_8009EF24(*(void *)0x800803DC, arg3) < 0x81) {
                                var_s1 = 0;
                                if ((func_80099330(((s32) (M2C_FIELD(arg3, u16 *, 0x2A) << 0x10) >> 0x19) & 0xFFFF, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20)) << 0x10) != 0) {
                                    goto block_59;
                                }
                            }
                            goto block_40;
                        }
                        goto block_39;
                    }
block_37:
                    goto block_38;
                }
                goto block_59;
            }
            goto block_40;
        }
block_38:
        func_8009FB34(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
block_39:
        var_s1 = 0;
block_40:
loop_41:
        temp_v1_3 = (s16) M2C_FIELD(arg3, u16 *, 0x2A);
        temp_v0_6 = var_s1 << 0x10;
        if (M2C_FIELD(arg0, u16 *, 0x98) & 2) {
            var_s0 = temp_v1_3 - *((temp_v0_6 >> 0xF) + &D_8006BDD0);
        } else {
            var_s0 = temp_v1_3 + *((temp_v0_6 >> 0xF) + &D_8006BDD0);
        }
        if ((func_800996B0(var_s0, arg2, arg3, 0x20) << 0x10) > 0) {
            if ((var_s1 < 3) || (var_s6 == 0)) {
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) var_s0;
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) + 1);
                var_a2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2 = 0x300;
                }
                func_800991C0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
                temp_a0_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(arg2, u8 *, 0x24) + *(temp_a0_2 + &D_8006BDA8));
                M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a0_2 + &D_8006BDB8));
                var_a2_2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2_2 = 0x300;
                }
                func_8009900C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
                var_v0 = var_s1 << 0x10;
                goto block_56;
            }
            goto block_59;
        }
        var_v0_2 = var_s1 + 1;
        if (((var_s1 << 0x10) != 0) || (var_v0_2 = var_s1 + 1, (*(u16 *)0x800814B4 == (u16) M2C_FIELD(arg2, u8 *, 0x24))) || (var_v0_2 = var_s1 + 1, ((func_80098F70(arg3, M2C_FIELD(*(void *)0x800803DC, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
            var_s1 = var_v0_2;
            var_v0 = var_s1 << 0x10;
            if (var_v0_2 >= 8) {
block_56:
                if ((var_v0 >> 0x10) >= 8) {
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                    func_800A86C4(arg3);
                    return;
                }
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg0, s8 *, 0x9C) = (s8) (u8) M2C_FIELD(arg2, s8 *, 0x26);
                M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
                M2C_FIELD(&D_80085990, u16 *, 8) = (u16) (M2C_FIELD(&D_80085990, u16 *, 8) + 1);
                if ((s8) M2C_FIELD(arg3, u8 *, 0x6D) == 0) {
block_59:
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    return;
                }
                temp_v0_7 = func_800BB784((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
                if (temp_v0_7 < 0x200) {
                    M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_7;
                }
            } else {
                goto loop_41;
            }
        }
    }
}
