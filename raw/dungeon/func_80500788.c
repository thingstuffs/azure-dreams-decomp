#include "common.h"
#include "m2c_compat.h"

s16 func_800BCB04(s32, s32, M2C_UNK);               /* extern */
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E2970;

s32 func_80017F88(s16 arg0, s16 *arg1, s16 *arg2, s16 arg3) {
    s32 sp10;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_s1;
    s16 var_s3;
    s16 var_s6;
    s16 var_v0_2;
    s32 var_v0;
    u16 temp_v1_3;
    u16 var_s0;
    u16 var_s2;
    void *temp_v0;
    void *temp_v0_3;

    var_s3 = -0x200;
    temp_v0 = (arg0 * 0x14) + &D_800E2970;
    temp_v1 = M2C_FIELD(temp_v0, s16 *, 6);
    var_s2 = M2C_FIELD(temp_v0, u16 *, 2);
    var_s6 = temp_v1;
    sp10 = M2C_FIELD(&D_8008333C, s32 *, 0);
    if (temp_v1 > 0) {
        do {
            temp_v0_3 = (arg0 * 0x14) + &D_800E2970;
            temp_v1_2 = M2C_FIELD(temp_v0_3, s16 *, 4);
            var_s0 = M2C_FIELD(temp_v0_3, u16 *, 0);
            var_s1 = temp_v1_2;
            if (temp_v1_2 > 0) {
                do {
                    temp_v1_3 = M2C_FIELD(((((s16) var_s0 + ((s16) var_s2 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + sp10), u16 *, 4);
                    var_v0_2 = var_s1 - 1;
                    if (!(temp_v1_3 & 0x8400) && ((arg3 == 0) || (var_v0_2 = var_s1 - 1, ((temp_v1_3 & 0x300) == 0x200)))) {
                        temp_v0_4 = func_800BCB04((((s16) var_s0 << 6) + 0x20) & 0xFFE0, (((s16) var_s2 << 6) + 0x20) & 0xFFFF, -0x400);
                        if (temp_v0_4 < 0x200) {
                            var_v0_2 = var_s1 - 1;
                            if (var_s3 < temp_v0_4) {
                                *arg1 = var_s0;
                                var_s3 = temp_v0_4;
                                *arg2 = var_s2;
                                goto block_10;
                            }
                        } else {
block_10:
                            var_v0_2 = var_s1 - 1;
                        }
                    }
                    var_s1 = var_v0_2;
                    var_s0 += 1;
                } while ((var_v0_2 << 0x10) > 0);
            }
            temp_v0_2 = var_s6 - 1;
            var_s6 = temp_v0_2;
            var_s2 += 1;
        } while ((temp_v0_2 << 0x10) > 0);
    }
    var_v0 = var_s3 << 0x10;
    if (var_s3 == -0x200) {
        var_v0 = 0x200 << 0x10;
    }
    return var_v0 >> 0x10;
}
