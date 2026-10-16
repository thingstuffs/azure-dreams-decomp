#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80040AA0(u8, M2C_UNK *, s32 *);        /* extern */
s32 func_800429E4(s32);                             /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_800481E0();                            /* extern */
M2C_UNK func_800945E8(void *);                      /* extern */
M2C_UNK func_800948BC();                            /* extern */
M2C_UNK func_80094E34();                            /* extern */
s32 func_800990FC(M2C_UNK, void *);                 /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_8009929C(M2C_UNK, s32);                    /* extern */
s32 func_80099734(void *, s32);                     /* extern */
M2C_UNK func_800A56E0(M2C_UNK, void *);             /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
M2C_UNK func_800A6780();                            /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK, u8);         /* extern */
M2C_UNK func_800C542C(s32, s16, s16, M2C_UNK);      /* extern */
M2C_UNK func_8015FF1C();                            /* static */
extern s32 D_80010234;
extern s32 D_80012090;
extern M2C_UNK D_80081468;
extern s16 D_8008146C;
extern u8 D_80082E6B;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern s32 D_80083788;
extern u16 D_8008378A;
extern M2C_UNK D_800DCED4;
extern M2C_UNK D_800E2348;
extern M2C_UNK D_800E2368;
extern void *D_800E3D7C;
extern M2C_UNK D_8015E940;
extern M2C_UNK D_8015E950;
extern M2C_UNK D_8015E988;
extern M2C_UNK D_8015E994;
extern M2C_UNK D_8015E9B8;

void func_80163CD8(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_a0;
    s16 temp_a0_2;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s16 var_s1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u8 temp_a0;
    u8 temp_a2;
    u8 temp_v0;
    u8 temp_v1;
    u8 var_v0_4;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        temp_a2 = M2C_FIELD(arg2, u8 *, 0x25);
        var_v0 = M2C_FIELD(&D_80082E80, u8 *, 0x24) - M2C_FIELD(arg2, u8 *, 0x24);
        if (var_v0 < 0) {
            var_v0 = -var_v0;
        }
        var_v1 = M2C_FIELD(&D_80082E80, u8 *, 0x25) - temp_a2;
        if (var_v1 < 0) {
            var_v1 = -var_v1;
        }
        M2C_FIELD(arg0, s16 *, 0x96) = (s16) (((var_v0 + var_v1) * 4) + 9);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        func_800AD594(arg3, 0x2000, temp_a2);
        temp_v0 = M2C_FIELD(arg2, u8 *, 0x24);
        if (M2C_FIELD(&D_80082E80, u8 *, 0x24) == temp_v0) {
            var_a1 = 6;
            if ((u8) M2C_FIELD(arg2, u8 *, 0x25) < (u8) M2C_FIELD(&D_80082E80, u8 *, 0x25)) {
                var_a1 = 2;
            }
        } else {
            temp_a0 = M2C_FIELD(arg2, u8 *, 0x25);
            if (M2C_FIELD(&D_80082E80, u8 *, 0x25) == temp_a0) {
                var_a1 = (temp_v0 >= (u8) M2C_FIELD(&D_80082E80, u8 *, 0x24)) * 4;
            } else {
                temp_v0_2 = temp_a0 < (u8) M2C_FIELD(&D_80082E80, u8 *, 0x25);
                if (temp_v0 < (u8) M2C_FIELD(&D_80082E80, u8 *, 0x24)) {
                    var_a1 = 7;
                    if (temp_v0_2 != 0) {
                        var_a1 = 1;
                    }
                } else {
                    var_a1 = 5;
                    if (temp_v0_2 != 0) {
                        var_a1 = 3;
                    }
                }
            }
        }
        M2C_FIELD(arg3, s16 *, 0x2A) = (s16) (var_a1 << 9);
        if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
            if ((s32) M2C_FIELD(arg3, u8 *, 0x11) >= D_8008146C) {
                var_s1 = 0;
                do {
                    temp_s0 = M2C_FIELD(((var_s1 * 4) + D_800E3D7C), s32 *, 0xAC);
                    if ((temp_s0 != 0) && (temp_s0 != arg3)) {
                        func_800C542C(temp_s0, *((func_800429E4(temp_s0) * 2) + &D_800DCED4), var_s1, 0);
                    }
                    var_s1 += 1;
                } while (var_s1 < 2);
            }
        } else {
        case 1:
        }
        temp_a0_2 = M2C_FIELD(arg0, s16 *, 0x96);
        temp_a1 = ((M2C_FIELD(&D_80082E80, u8 *, 0x24) << 6) + 0x20) << 0x10;
        var_a2 = ((M2C_FIELD(&D_80082E80, u8 *, 0x25) << 6) + 0x20) << 0x10;
        var_a3 = D_80083788 + 0xFFA00000;
        if (temp_a0_2 >= 0xE) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1 - M2C_FIELD(arg1, s32 *, 0)) / (s32) (temp_a0_2 - 9));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) (M2C_FIELD(arg0, s16 *, 0x96) - 9));
            var_v1_2 = var_a3 - M2C_FIELD(arg0, s32 *, 0x90);
            var_v0_2 = M2C_FIELD(arg0, s16 *, 0x96) - 9;
            goto block_57;
        }
        if (temp_a0_2 >= 0xB) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1 - M2C_FIELD(arg1, s32 *, 0)) / (s32) (temp_a0_2 - 7));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) (M2C_FIELD(arg0, s16 *, 0x96) - 7));
            var_v1_2 = var_a3 - M2C_FIELD(arg0, s32 *, 0x90);
            var_v0_2 = M2C_FIELD(arg0, s16 *, 0x96) - 7;
            goto block_57;
        }
        var_v1_3 = temp_a0_2 - 2;
        if (temp_a0_2 >= 5) {
            var_v0_3 = temp_a1 - M2C_FIELD(arg1, s32 *, 0);
block_56:
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (var_v0_3 / var_v1_3);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) (M2C_FIELD(arg0, s16 *, 0x96) - 2));
            var_v1_2 = var_a3 - M2C_FIELD(arg0, s32 *, 0x90);
            var_v0_2 = M2C_FIELD(arg0, s16 *, 0x96) - 2;
block_57:
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (var_v1_2 / var_v0_2);
        } else {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1 - M2C_FIELD(arg1, s32 *, 0)) / temp_a0_2);
block_59:
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (var_a3 - M2C_FIELD(arg0, s32 *, 0x90)) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        }
block_60:
        temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            return;
        }
    default:
        return;
    case 2:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2368;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2368), 0);
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        func_80094E34();
        return;
    case 3:
        temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x96);
        M2C_FIELD(arg0, s16 *, 0x96) = (s16) (temp_v0_4 + 1);
        if ((s16) temp_v0_4 >= 7) {
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            M2C_FIELD(D_800E3D7C, s32 *, 0x14) = (s32) (M2C_FIELD(D_800E3D7C, s32 *, 0x14) | 0x100000);
            func_800A56E0(0x603, D_800E3D7C);
            return;
        }
        break;
    case 4:
        M2C_FIELD(arg1, s32 *, 0x14) = -0xC0000;
        M2C_FIELD(&D_80083780, s32 *, 8) = (s32) (M2C_FIELD(&D_80083780, s32 *, 8) + 0xFFF40000);
        temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0x96);
        M2C_FIELD(arg0, s16 *, 0x96) = (s16) (temp_v0_5 + 1);
        if ((s16) temp_v0_5 >= 0x1B) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
                if ((s32) M2C_FIELD(arg3, u8 *, 0x11) >= D_8008146C) {
                    var_v0_4 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_43:
                    M2C_FIELD(arg0, u8 *, 0x9B) = var_v0_4;
                    return;
                }
                goto block_41;
            }
block_41:
            M2C_FIELD(arg0, u8 *, 0x9B) = 7U;
            return;
        }
        break;
    case 5:
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        var_v0_4 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
        goto block_43;
    case 6:
        func_800945E8(D_800E3D7C);
        func_800948BC();
        func_800A6780();
        D_80010234 += 1;
        M2C_FIELD(&D_80081468, u16 *, 4) = (u16) (M2C_FIELD(&D_80081468, u16 *, 4) + 1);
        func_80040AA0(D_80082E6B, &D_80081468, &D_80010234);
        func_800481E0();
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, s16 *, 0x96) = 0;
        M2C_FIELD(arg0, u8 *, 0x9B) = 0x14U;
block_63:
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        break;
    case 7:
        temp_v1_2 = &D_80083498 + 0x20;
        M2C_FIELD(D_800E3D7C, s32 *, 0x14) = (s32) (M2C_FIELD(D_800E3D7C, s32 *, 0x14) & 0xFFEFFFFF);
        temp_v0_6 = D_8008378A - M2C_FIELD(temp_v1_2, u16 *, 0x88);
        M2C_FIELD(D_800E3D7C, u16 *, 0x92) = temp_v0_6;
        M2C_FIELD(temp_v1_2, u16 *, 0x88) = temp_v0_6;
        M2C_FIELD(temp_v1_2, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x1C) | 0x40000000);
        M2C_FIELD(arg0, s16 *, 0x96) = 0x28;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        if ((D_80012090 != 0) || (D_8008146C != 0x28)) {
            var_s0 = func_800990FC(0x40000000, D_800E3D7C);
            var_a0 = &D_8015E994;
            var_a1_2 = func_80099734(arg3, func_80099194(&D_8015E988, func_8009929C(0xA, func_80099194(&D_8015E950, func_8009929C(0xA, func_80099194(&D_8015E940, var_s0))))));
        } else {
            var_s0 = func_800990FC(0x40000000, D_800E3D7C);
            var_a0 = &D_8015E9B8;
            var_a1_2 = var_s0;
        }
        func_80099290(func_80099194(var_a0, var_a1_2));
        func_800A5720(var_s0);
        /* fallthrough */
    case 8:
        temp_a1_2 = ((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10;
        var_a2 = ((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10;
        temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x96);
        var_a3 = (M2C_FIELD(arg0, s16 *, 0xB4) - 0x20) << 0x10;
        if (temp_v1_3 >= 0xE) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 0)) / (s32) (temp_v1_3 - 9));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) (M2C_FIELD(arg0, s16 *, 0x96) - 9));
            var_v1_2 = var_a3 - M2C_FIELD(arg0, s32 *, 0x90);
            var_v0_2 = M2C_FIELD(arg0, s16 *, 0x96) - 9;
            goto block_57;
        }
        if (temp_v1_3 >= 0xB) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 0)) / (s32) (temp_v1_3 - 7));
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (var_a2 - M2C_FIELD(arg1, s32 *, 4)) / (s32) (M2C_FIELD(arg0, s16 *, 0x96) - 7));
            var_v1_2 = var_a3 - M2C_FIELD(arg0, s32 *, 0x90);
            var_v0_2 = M2C_FIELD(arg0, s16 *, 0x96) - 7;
            goto block_57;
        }
        if (temp_v1_3 >= 5) {
            var_v1_3 = temp_v1_3 - 2;
            var_v0_3 = temp_a1_2 - M2C_FIELD(arg1, s32 *, 0);
            goto block_56;
        }
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (temp_a1_2 - M2C_FIELD(arg1, s32 *, 0)) / temp_v1_3);
        goto block_59;
        goto block_60;
    case 9:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_8015FF1C;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
        D_8008346C = 0;
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_800E2348;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_800E2348), 0);
        M2C_FIELD(arg2, s8 *, 5) = 1;
        M2C_FIELD(arg0, u16 *, 0xA2) = 0U;
        M2C_FIELD(arg0, s16 *, 0x9E) = 0;
        M2C_FIELD(arg0, u16 *, 0x92) = -0x20U;
        M2C_FIELD(arg3, u16 *, 0x88) = (u16) M2C_FIELD(arg0, s16 *, 0xB4);
        M2C_FIELD(arg1, s16 *, 2) = (s16) ((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20);
        M2C_FIELD(arg1, s16 *, 6) = (s16) ((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20);
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((M2C_FIELD(arg3, u16 *, 0x88) + M2C_FIELD(arg0, u16 *, 0x92)) - M2C_FIELD(arg0, u16 *, 0xA2));
        goto block_63;
    }
}
