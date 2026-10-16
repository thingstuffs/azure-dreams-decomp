#include "common.h"
#include "m2c_compat.h"

s32 func_8001CE14(s16, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK func_8001E108(u16, s32, s16 *, M2C_UNK, s32); /* extern */
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E2970;
extern M2C_UNK D_800EA000;

void func_8001DE2C(void) {
    M2C_UNK *var_s3;
    M2C_UNK var_a3;
    s16 *temp_s0;
    s32 temp_s6;
    s32 temp_s7;
    s32 temp_v0;
    s32 var_fp;
    u16 var_s1;
    u16 var_s2;

    var_fp = 0;
    var_s3 = &D_800E2970;
    do {
        if (M2C_FIELD(var_s3, s16 *, 0xA) != 0) {
            var_s2 = M2C_FIELD(var_s3, u16 *, 2);
            temp_s6 = M2C_FIELD(var_s3, u16 *, 0) + M2C_FIELD(var_s3, u16 *, 4);
            temp_s7 = var_s2 + M2C_FIELD(var_s3, u16 *, 6);
            if ((s32) var_s2 < temp_s7) {
                do {
                    var_s1 = M2C_FIELD(var_s3, u16 *, 0);
                    if ((s32) var_s1 < temp_s6) {
                        do {
                            temp_s0 = (((var_s2 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_s1) * 6) + &D_800EA000;
                            if (func_8001CE14(*temp_s0, 0x13, 0x1C) != 0) {
                                func_8001E108(var_s1, (s32) var_s2, temp_s0, 0x13, 0x20);
                                temp_v0 = var_s1 & 1;
                                if (var_s2 & 1) {
                                    if (temp_v0 == 0) {
                                        var_s1 += 1;
                                    } else {
                                        goto block_9;
                                    }
                                } else {
                                    if (temp_v0 == 0) {
block_9:
                                        *temp_s0 = (u16) *temp_s0 + 0xA;
                                    }
                                    goto block_27;
                                }
                            } else {
                                if (func_8001CE14(*temp_s0, 0x27, 0x30) != 0) {
                                    var_a3 = 0x27;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x31, 0x3A) != 0) {
                                    var_a3 = 0x31;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x3B, 0x44) != 0) {
                                    var_a3 = 0x3B;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x45, 0x4E) != 0) {
                                    var_a3 = 0x45;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x6B, 0x6F) != 0) {
                                    var_a3 = 0x6B;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x70, 0x74) != 0) {
                                    var_a3 = 0x70;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x75, 0x79) != 0) {
                                    var_a3 = 0x75;
                                    goto block_26;
                                }
                                if (func_8001CE14(*temp_s0, 0x7A, 0x7E) != 0) {
                                    var_a3 = 0x7A;
block_26:
                                    func_8001E108(var_s1, (s32) var_s2, temp_s0, var_a3);
                                }
block_27:
                                var_s1 += 1;
                            }
                        } while ((s32) var_s1 < temp_s6);
                    }
                    var_s2 += 1;
                } while ((s32) var_s2 < temp_s7);
            }
        }
        var_fp += 1;
        var_s3 += 0x14;
    } while (var_fp < 0x24);
}
