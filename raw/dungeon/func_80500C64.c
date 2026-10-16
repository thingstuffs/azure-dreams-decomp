#include "common.h"
#include "m2c_compat.h"

s32 func_800199C8(s16);                             /* extern */
M2C_UNK func_8003E4FC(M2C_UNK, s32, M2C_UNK);       /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8004068C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s32 func_800A7A38(M2C_UNK *);                       /* extern */
s16 func_800BCA68(s32, s32);                        /* extern */
extern s16 D_8001F586;
extern M2C_UNK D_8001F604;
extern s16 D_8008146E;
extern void *D_80081480;
extern void *D_8008148C;
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800DF258;
extern s32 D_800E296C;
extern M2C_UNK D_800E2970;
extern M2C_UNK D_800E2C40;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E36C8;
extern M2C_UNK D_800E39C8;
extern M2C_UNK D_800E3CD8;
extern s32 D_800E3D6C;
extern M2C_UNK D_800EA000;

void func_80018464(s32 arg0) {
    M2C_UNK *var_a1;
    M2C_UNK *var_s0_6;
    M2C_UNK *var_s1;
    M2C_UNK *var_s1_2;
    M2C_UNK *var_s1_3;
    M2C_UNK *var_s1_4;
    M2C_UNK *var_s2_2;
    M2C_UNK *var_s2_3;
    s16 *var_v1;
    s16 temp_v0_5;
    s16 var_s3;
    s16 var_s3_2;
    s32 temp_a2;
    s32 temp_s5;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    u16 temp_v0;
    u16 temp_v1;
    u16 temp_v1_2;
    u8 *var_s0_2;
    u8 temp_a0;
    u8 var_v1_2;
    u8 var_v1_4;
    void *temp_s0;
    void *temp_s0_10;
    void *temp_s0_11;
    void *temp_s0_12;
    void *temp_s0_13;
    void *temp_s0_14;
    void *temp_s0_15;
    void *temp_s0_16;
    void *temp_s0_17;
    void *temp_s0_18;
    void *temp_s0_19;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s0_6;
    void *temp_s0_7;
    void *temp_s0_8;
    void *temp_s0_9;
    void *temp_v0_2;
    void *var_a0;
    void *var_a2;
    void *var_s0;
    void *var_s0_3;
    void *var_s0_4;
    void *var_s0_5;
    void *var_s2;
    void *var_v1_3;
    void *var_v1_5;
    void *var_v1_6;

    temp_s0 = D_8008148C;
    D_80081480 = temp_s0;
    temp_s5 = M2C_FIELD(&D_8008333C, s32 *, 0);
    func_8003E4FC(6, *(((s32) ((arg0 - 1) << 0x10) >> 0xE) + &D_8001F604), 0);
    var_s3 = 0;
    func_8003F320();
    var_a2 = temp_s0 + 4;
    temp_v1 = M2C_FIELD(temp_s0, u16 *, 0);
    M2C_FIELD(&D_8008333C, u16 *, 0x14) = temp_v1;
    M2C_FIELD(&D_8008333C, s16 *, 0x18) = (s16) ((1 << (s16) temp_v1) - 1);
    temp_v0 = M2C_FIELD(temp_s0, u16 *, 2);
    M2C_FIELD(&D_8008333C, s16 *, 0x1C) = (s16) (0x40 << (s16) temp_v1);
    M2C_FIELD(&D_8008333C, u16 *, 0x16) = temp_v0;
    M2C_FIELD(&D_8008333C, s16 *, 0x1A) = (s16) ((1 << (s16) temp_v0) - 1);
    M2C_FIELD(&D_8008333C, s16 *, 0x1E) = (s16) (0x40 << (s16) temp_v0);
    if (M2C_FIELD(var_a2, u16 *, 4) != 0) {
        var_a1 = &D_800E2970;
        do {
            M2C_FIELD(var_a1, s16 *, 0xA) = 1;
            M2C_FIELD(var_a1, u16 *, 0) = (u16) M2C_FIELD(var_a2, u16 *, 0);
            M2C_FIELD(var_a1, u16 *, 2) = (u16) M2C_FIELD(var_a2, u16 *, 2);
            M2C_FIELD(var_a1, u16 *, 4) = (u16) M2C_FIELD(var_a2, u16 *, 4);
            var_s0 = var_a2 + 8;
            M2C_FIELD(var_a1, s16 *, 0xE) = 0;
            M2C_FIELD(var_a1, u16 *, 6) = (u16) M2C_FIELD(var_a2, u16 *, 6);
            temp_a2 = var_s3 << 6;
            if (M2C_FIELD(var_a2, u8 *, 8) != 0) {
                do {
                    M2C_FIELD(var_a1, void **, 0x10) = (void *) (temp_a2 + &D_800E2C40);
                    temp_s0_4 = var_s0 + 1;
                    *((M2C_FIELD(var_a1, s16 *, 0xE) * 4) + temp_a2 + &D_800E2C40) = M2C_FIELD(var_s0, u8 *, 0);
                    temp_s0_3 = temp_s0_4 + 1;
                    M2C_FIELD(((M2C_FIELD(var_a1, s16 *, 0xE) * 4) + temp_a2 + &D_800E2C40), u8 *, 1) = (u8) M2C_FIELD(var_s0, u8 *, 1);
                    M2C_FIELD(((M2C_FIELD(var_a1, s16 *, 0xE) * 4) + temp_a2 + &D_800E2C40), s16 *, 2) = (s16) M2C_FIELD(temp_s0_4, u8 *, 1);
                    var_s0 = temp_s0_3 + 2;
                    M2C_FIELD(var_a1, s16 *, 0xE) = (s16) ((u16) M2C_FIELD(var_a1, s16 *, 0xE) + 1);
                } while (M2C_FIELD(temp_s0_3, u8 *, 2) != 0);
            }
            var_a1 += 0x14;
            var_s3 += 1;
            temp_s0_2 = var_s0 + 2;
            var_a2 = temp_s0_2;
        } while (M2C_FIELD(temp_s0_2, u16 *, 4) != 0);
    }
    var_s0_2 = var_a2 + 8;
    D_8008146E = var_s3;
    var_s3_2 = 0;
    if (M2C_FIELD(var_a2, u8 *, 8) != 0) {
        var_s2 = var_s0_2 + 1;
        var_s1 = &D_800E3CD8;
        do {
            M2C_FIELD(var_s1, s16 *, 0) = (s16) (M2C_FIELD(var_s2, u8 *, 1) + 2);
            M2C_FIELD(var_s1, s16 *, 2) = (s16) *var_s0_2;
            M2C_FIELD(var_s1, s16 *, 4) = (s16) M2C_FIELD(var_s2, u8 *, 0);
            temp_v0_2 = ((*var_s0_2 + (M2C_FIELD(var_s2, u8 *, 0) << (s16) M2C_FIELD(&D_8008333C, u16 *, 0x14))) * 6) + temp_s5;
            temp_v1_2 = M2C_FIELD(temp_v0_2, u16 *, 2) - 0x20;
            M2C_FIELD(temp_v0_2, u16 *, 2) = temp_v1_2;
            M2C_FIELD(var_s1, u16 *, 6) = temp_v1_2;
            if (M2C_FIELD(var_s1, s16 *, 0) == 2) {
                *(((*var_s0_2 + (M2C_FIELD(var_s2, u8 *, 0) << (s16) M2C_FIELD(&D_8008333C, u16 *, 0x14))) * 6) + temp_s5) = 1;
            }
            var_s1 += 8;
            var_s3_2 += 1;
            temp_a0 = *var_s0_2;
            var_s0_2 += 4;
            func_8009A21C(temp_a0, M2C_FIELD(var_s2, u8 *, 0), 0x20);
            var_s2 += 4;
        } while (*var_s0_2 != 0);
    }
    if (func_800199C8(var_s3_2) != 0) {
        var_s3_2 += 1;
    }
    D_8001F586 = 1;
    var_s3_3 = var_s3_2 + 1;
    if (var_s3_3 < 4) {
        var_v1 = (var_s3_3 * 8) + &D_800E3CD8;
        do {
            *var_v1 = 0;
            var_s3_3 += 1;
            var_v1 += 8;
        } while (var_s3_3 < 4);
    }
    var_s0_3 = var_s0_2 + 2;
    var_v1_2 = M2C_FIELD(var_s0_2, u8 *, 2);
    var_s3_4 = 0;
    if (var_v1_2 != 0) {
        var_s1_2 = &D_800E3548;
        var_s2_2 = &D_800E36C8;
loop_18:
        if (var_v1_2 == 0x63) {
            var_s0_3 += 6;
            D_800E3D6C |= 2;
        } else {
            temp_s0_5 = var_s0_3 + 1;
            M2C_FIELD(var_s2_2, u8 *, 0) = var_v1_2;
            temp_s0_6 = temp_s0_5 + 1;
            var_s3_4 += 1;
            M2C_FIELD(var_s2_2, u8 *, 1) = (u8) M2C_FIELD(var_s0_3, u8 *, 1);
            temp_s0_7 = temp_s0_6 + 1;
            M2C_FIELD(var_s1_2, u8 *, 0) = (u8) M2C_FIELD(temp_s0_5, u8 *, 1);
            temp_s0_8 = temp_s0_7 + 1;
            M2C_FIELD(var_s1_2, u8 *, 1) = (u8) M2C_FIELD(temp_s0_6, u8 *, 1);
            temp_s0_9 = temp_s0_8 + 1;
            M2C_FIELD(var_s1_2, u8 *, 3) = (u8) M2C_FIELD(temp_s0_7, u8 *, 1);
            var_s0_3 = temp_s0_9 + 1;
            M2C_FIELD(var_s1_2, u8 *, 2) = (u8) M2C_FIELD(temp_s0_8, u8 *, 1);
            temp_v0_3 = func_800A7A38(var_s1_2);
            var_s1_2 += 4;
            M2C_FIELD(var_s2_2, s32 *, 8) = temp_v0_3;
            var_v1_2 = M2C_FIELD(temp_s0_9, u8 *, 1);
            var_s2_2 += 0xC;
            if (var_v1_2 != 0) {
                goto loop_18;
            }
        }
    }
    if (var_s3_4 < 0x40) {
        var_v1_3 = (var_s3_4 * 4) + &D_800E3548;
        do {
            M2C_FIELD(var_v1_3, s8 *, 1) = 0;
            M2C_FIELD(var_v1_3, s8 *, 0) = 0;
            var_s3_4 += 1;
            var_v1_3 += 4;
        } while (var_s3_4 < 0x40);
    }
    var_s0_4 = var_s0_3 + 2;
    var_v1_4 = M2C_FIELD(var_s0_3, u8 *, 2);
    var_s3_5 = 0;
    if (var_v1_4 != 0) {
        var_s2_3 = &D_800E3648;
        var_s1_3 = &D_800E39C8;
loop_26:
        if (var_v1_4 == 0x63) {
            var_s0_4 += 6;
            D_800E3D6C |= 8;
        } else {
            temp_s0_10 = var_s0_4 + 1;
            M2C_FIELD(var_s1_3, u8 *, 6) = var_v1_4;
            temp_s0_11 = temp_s0_10 + 1;
            var_s3_5 += 1;
            M2C_FIELD(var_s1_3, u8 *, 7) = (u8) M2C_FIELD(var_s0_4, u8 *, 1);
            temp_s0_12 = temp_s0_11 + 1;
            M2C_FIELD(var_s2_3, u8 *, 0) = (u8) M2C_FIELD(temp_s0_10, u8 *, 1);
            temp_s0_13 = temp_s0_12 + 1;
            M2C_FIELD(var_s2_3, u8 *, 1) = (u8) M2C_FIELD(temp_s0_11, u8 *, 1);
            temp_s0_14 = temp_s0_13 + 1;
            M2C_FIELD(var_s2_3, u8 *, 3) = (u8) M2C_FIELD(temp_s0_12, u8 *, 1);
            var_s0_4 = temp_s0_14 + 1;
            M2C_FIELD(var_s2_3, u8 *, 2) = (u8) M2C_FIELD(temp_s0_13, u8 *, 1);
            temp_v0_4 = *((M2C_FIELD(var_s2_3, u8 *, 0) * 4) + &D_800DF258);
            var_s2_3 += 4;
            M2C_FIELD(var_s1_3, s32 *, 8) = temp_v0_4;
            func_8009A21C(M2C_FIELD(var_s1_3, u8 *, 6), M2C_FIELD(var_s1_3, u8 *, 7), 0x20);
            var_v1_4 = M2C_FIELD(temp_s0_14, u8 *, 1);
            var_s1_3 += 0x18;
            if (var_v1_4 != 0) {
                goto loop_26;
            }
        }
    }
    var_s0_5 = var_s0_4 + 2;
    if (M2C_FIELD(var_s0_4, u8 *, 2) != 0) {
        var_a0 = (var_s3_5 * 4) + &D_800E3648;
        var_v1_5 = (var_s3_5 * 0x18) + &D_800E39C8;
        do {
            var_s3_5 += 1;
            D_800E296C |= 0x10000000;
            temp_s0_16 = var_s0_5 + 1;
            M2C_FIELD(var_v1_5, u8 *, 6) = (u8) M2C_FIELD(var_s0_5, u8 *, 0);
            temp_s0_17 = temp_s0_16 + 1;
            M2C_FIELD(var_v1_5, u8 *, 7) = (u8) M2C_FIELD(var_s0_5, u8 *, 1);
            temp_s0_18 = temp_s0_17 + 1;
            var_v1_5 += 0x18;
            M2C_FIELD(var_a0, u8 *, 0) = (u8) M2C_FIELD(temp_s0_16, u8 *, 1);
            temp_s0_19 = temp_s0_18 + 1;
            M2C_FIELD(var_a0, u8 *, 1) = (u8) M2C_FIELD(temp_s0_17, u8 *, 1);
            temp_s0_15 = temp_s0_19 + 1;
            M2C_FIELD(var_a0, u8 *, 3) = (u8) M2C_FIELD(temp_s0_18, u8 *, 1);
            var_s0_5 = temp_s0_15 + 1;
            M2C_FIELD(var_a0, u8 *, 2) = (u8) M2C_FIELD(temp_s0_19, u8 *, 1);
            var_a0 += 4;
        } while (M2C_FIELD(temp_s0_15, u8 *, 1) != 0);
    }
    if (var_s3_5 < 0x20) {
        var_v1_6 = (var_s3_5 * 4) + &D_800E3648;
        do {
            M2C_FIELD(var_v1_6, s8 *, 1) = 0;
            M2C_FIELD(var_v1_6, s8 *, 0) = 0;
            var_s3_5 += 1;
            var_v1_6 += 4;
        } while (var_s3_5 < 0x20);
    }
    func_8004068C(var_s0_5 + 2, &D_800EA000);
    var_s1_4 = &D_800E3548;
    if (M2C_FIELD(&D_800E3548, u8 *, 1) != 0) {
        var_s0_6 = &D_800E36C8;
        do {
            var_s1_4 += 4;
            temp_v0_5 = func_800BCA68(M2C_FIELD(var_s0_6, u8 *, 0) << 6, M2C_FIELD(var_s0_6, u8 *, 1) << 6);
            M2C_FIELD(var_s0_6, s16 *, 4) = temp_v0_5;
            M2C_FIELD(var_s0_6, s16 *, 2) = temp_v0_5;
            var_s0_6 += 0xC;
        } while (M2C_FIELD(var_s1_4, u8 *, 1) != 0);
    }
}
