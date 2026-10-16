#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800194C4(s16);                         /* extern */
M2C_UNK func_80019648(M2C_UNK);                     /* extern */
s32 func_80019684(s16, M2C_UNK, M2C_UNK, M2C_UNK);  /* extern */
M2C_UNK func_80019A74();                            /* extern */
s32 func_80033BC0(M2C_UNK, s16, void *);            /* extern */
M2C_UNK func_80044698();                            /* extern */
M2C_UNK func_80048088(M2C_UNK);                     /* extern */
M2C_UNK func_80053DA8(M2C_UNK);                     /* extern */
M2C_UNK func_800542BC();                            /* extern */
s32 func_800A6D30(M2C_UNK, s16, void *);            /* extern */
s32 func_800A6DA4(M2C_UNK, M2C_UNK, s8 *, s8);      /* extern */
extern s8 D_80080A88;
extern M2C_UNK D_80081468;
extern s16 D_8008146C;
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern void *D_80083478;
extern s8 D_800DDC9C;
extern s8 D_800DDCA4;
extern s8 D_800DDCAC;
extern s8 D_800DDCB4;
extern s32 D_800E296C;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E39C8;

s32 func_80018E80(void) {
    M2C_UNK var_a0;
    s16 var_s0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_s2;
    s32 var_s3;
    s8 *var_a1;
    s8 *var_a1_2;
    s8 *var_a1_3;
    s8 *var_a1_4;
    s8 *var_a2;
    s8 *var_a2_2;
    s8 *var_a2_3;
    s8 *var_a2_4;
    s8 temp_a3;
    s8 temp_a3_2;
    s8 temp_s0;
    s8 temp_s0_2;
    s8 temp_s0_3;
    s8 temp_s0_4;
    s8 var_a3;
    s8 var_a3_2;

    var_s3 = 0;
    temp_v1 = *(s32 *)0x8001022C;
    var_s2 = 0;
    if (temp_v1 == 1) {
        if (D_8008146C < 2) {
            *(s32 *)0x80012090 = temp_v1;
            func_80019648(0x80010000);
        } else if (*(s32 *)0x80012090 == temp_v1) {
            *(s32 *)0x80012090 = 0;
        }
    }
    if ((s32) D_80082E6B < 0x16) {
        if ((s32) D_80082E6B >= 0x12) {
            var_s3 = 0;
        } else {
            goto block_10;
        }
    } else {
block_10:
        temp_v1_2 = *(void *)0x80012090;
        switch (temp_v1_2) {                        /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            var_a0 = 0x66666667;
            var_s0 = D_8008146C / 5;
            if ((s16) (u16) D_8008146C >= 0x28) {
                var_s2 = 1;
                var_a0 = 0x10000000;
                D_800E296C |= 0x10000000;
            }
            switch ((s16) (u16) D_8008146C) {       /* switch 2; irregular */
            case 40:                                /* switch 2 */
                var_s3 = 1;
                var_s0 = 7;
                if (func_80033BC0(0xA2, (s16) (u16) D_8008146C, (void *)0x80010000) == 0) {
                    var_s0 = -1;
                    func_80019A74();
                }
                var_s2 = 1;
                break;
            default:                                /* switch 2 */
                var_s3 = (func_800A6D30(var_a0, (s16) (u16) D_8008146C, (void *)0x80010000) & 3) + 3;
                break;
            case 2:                                 /* switch 2 */
                if (*(void *)0x8001022C != 1) {
                    var_s3 = 2;
                    D_800E296C |= 0x10000000;
                } else if ((D_8008146C == 0x1F) && (func_80033BC0(0x1389, (s16) (u16) D_8008146C, (void *)0x80010000) == 0)) {
                    M2C_FIELD(&D_800E39C8, s8 *, 6) = 1;
                    M2C_FIELD(&D_800E39C8, s8 *, 7) = 1;
                    M2C_FIELD(&D_800E3648, s8 *, 0) = 0x37;
                    M2C_FIELD(&D_800E3648, s8 *, 1) = 0x13;
                    M2C_FIELD(&D_800E3648, s8 *, 3) = 0;
                    M2C_FIELD(&D_800E3648, s8 *, 2) = 0x63;
                    D_800E296C |= 0x10000000;
                }
                break;
            }
            if (var_s0 >= 0) {
                temp_v0 = func_80019684((s16) (var_s0 + 1), 1, 1);
                if (temp_v0 == 0) {
                    D_80080A88 = 0;
                }
                if (D_80080A88 == 0) {
                    func_80044698();
                    D_80080A88 = 1;
                    func_80053DA8(0x200);
                    func_800542BC();
                }
                if (temp_v0 == 0) {
                    func_80019684(0, 1, 0);
                }
            } else {
                func_80019684(0, 1, 0);
                func_80019684(0x29, 1, 1);
                func_80053DA8(0x200);
                func_800542BC();
                func_80048088(0x38);
            }
            if (var_s2 == 0) {
                func_800194C4(D_8008146C);
            }
            break;
        case 1:                                     /* switch 1 */
            var_s3 = 9;
            D_800E296C |= 0x10000000;
            func_80019684(1, 1, 1, 0x10000000);
            func_80053DA8(0x200);
            func_800542BC();
            func_80019684(0, 1, 0);
            break;
        case 2:                                     /* switch 1 */
            if (func_80019684((func_800A6D30(0x66660000) & 7) + 1, 1, 1) == 0) {
                func_80044698();
                func_80053DA8(0x200);
                func_800542BC();
                func_80019684(0, 1, 0);
            }
            if (M2C_FIELD(&D_80081468, s16 *, 4) == 1) {
                temp_s0 = func_800A6DA4(3, 0x2D) & 0xFFFF;
                var_a3 = M2C_FIELD(&D_80081468, s16 *, 4) + (func_800A6D30() & 1);
                var_a0_2 = 0;
                if (var_a3 >= 0x64) {
                    var_a3 = 0x63;
                }
                var_a1 = &D_800DDC9C;
                var_a2 = &D_800DDC9C + 1;
                do {
                    temp_v1_3 = var_a0_2 * 2;
                    *(temp_v1_3 + M2C_FIELD(&D_80083460, s32 *, 0x18)) = temp_s0;
                    var_a0_2 += 1;
                    M2C_FIELD((temp_v1_3 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 1) = var_a3;
                    *var_a2 = temp_s0;
                    *var_a1 = temp_s0;
                    var_a1 += 2;
                    var_a2 += 2;
                } while (var_a0_2 < 4);
                temp_s0_2 = func_800A6DA4(3, 0x2D, var_a2, var_a3) & 0xFFFF;
                var_a3_2 = D_8008146C + (func_800A6D30() & 1);
                var_a0_3 = 0;
                if (var_a3_2 >= 0x64) {
                    var_a3_2 = 0x63;
                }
                var_a1_2 = &D_800DDCA4;
                var_a2_2 = &D_800DDCA4 + 1;
                do {
                    temp_v1_4 = var_a0_3 * 2;
                    M2C_FIELD((temp_v1_4 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 8) = temp_s0_2;
                    var_a0_3 += 1;
                    M2C_FIELD((temp_v1_4 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 9) = var_a3_2;
                    *var_a2_2 = temp_s0_2;
                    *var_a1_2 = temp_s0_2;
                    var_a1_2 += 2;
                    var_a2_2 += 2;
                } while (var_a0_3 < 4);
            } else {
                M2C_FIELD(D_80083478, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(D_80083478, M2C_UNK *, 0x10));
                M2C_FIELD(D_80083478, M2C_UNK *, 4) = M2C_UNALIGNED32(M2C_FIELD(D_80083478, M2C_UNK *, 0x14));
                M2C_FIELD(D_80083478, M2C_UNK *, 8) = M2C_UNALIGNED32(M2C_FIELD(D_80083478, M2C_UNK *, 0x18));
                M2C_FIELD(D_80083478, M2C_UNK *, 0xC) = M2C_UNALIGNED32(M2C_FIELD(D_80083478, M2C_UNK *, 0x1C));
                var_a3_2 = (s8) &D_800DDC9C;
                var_a2_2 = M2C_UNALIGNED32(M2C_FIELD(&D_800DDC9C, M2C_UNK *, 0x18));
                M2C_FIELD((s8) &D_800DDC9C, M2C_UNK *, 0) = M2C_UNALIGNED32(M2C_FIELD(&D_800DDC9C, M2C_UNK *, 0x10));
                M2C_FIELD((s8) &D_800DDC9C, M2C_UNK *, 4) = M2C_UNALIGNED32(M2C_FIELD(&D_800DDC9C, M2C_UNK *, 0x14));
                M2C_FIELD((s8) &D_800DDC9C, M2C_UNK *, 8) = var_a2_2;
                M2C_FIELD((s8) &D_800DDC9C, M2C_UNK *, 0xC) = M2C_UNALIGNED32(M2C_FIELD(&D_800DDC9C, M2C_UNK *, 0x1C));
            }
            temp_s0_3 = func_800A6DA4(3, 0x2D, var_a2_2, var_a3_2) & 0xFFFF;
            var_a0_4 = 0;
            var_a1_3 = &D_800DDCAC;
            var_a2_3 = &D_800DDCAC + 1;
            temp_a3 = D_8008146C + (func_800A6D30() & 1);
            do {
                temp_v1_5 = var_a0_4 * 2;
                M2C_FIELD((temp_v1_5 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 0x10) = temp_s0_3;
                var_a0_4 += 1;
                M2C_FIELD((temp_v1_5 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 0x11) = temp_a3;
                *var_a2_3 = temp_s0_3;
                *var_a1_3 = temp_s0_3;
                var_a1_3 += 2;
                var_a2_3 += 2;
            } while (var_a0_4 < 4);
            temp_s0_4 = func_800A6DA4(3, 0x2D, var_a2_3, temp_a3) & 0xFFFF;
            var_a0_5 = 0;
            var_a1_4 = &D_800DDCB4;
            var_a2_4 = &D_800DDCB4 + 1;
            temp_a3_2 = D_8008146C + (func_800A6D30() & 1);
            do {
                temp_v1_6 = var_a0_5 * 2;
                M2C_FIELD((temp_v1_6 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 0x18) = temp_s0_4;
                var_a0_5 += 1;
                M2C_FIELD((temp_v1_6 + M2C_FIELD(&D_80083460, s32 *, 0x18)), s8 *, 0x19) = temp_a3_2;
                *var_a2_4 = temp_s0_4;
                *var_a1_4 = temp_s0_4;
                var_a1_4 += 2;
                var_a2_4 += 2;
            } while (var_a0_5 < 4);
            break;
        }
    }
    *(s32 *)0x80010234 = (s32) D_8008146C;
    return var_s3;
}
