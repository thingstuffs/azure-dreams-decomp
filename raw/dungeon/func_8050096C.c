#include "common.h"
#include "m2c_compat.h"

s16 func_800BCB04(s32, s32, M2C_UNK);               /* extern */
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E2970;

s16 func_8001816C(s16 arg0, s16 *arg1, s16 *arg2) {
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v1;
    s16 var_s0;
    s16 var_s2;
    s16 var_s5;
    u16 temp_v1_2;
    u16 var_s3;
    void *temp_a0;
    void *temp_v0_2;
    void *var_s1;

    temp_v0_2 = (arg0 * 0x14) + &D_800E2970;
    temp_v1 = M2C_FIELD(temp_v0_2, s16 *, 6);
    var_s3 = M2C_FIELD(temp_v0_2, u16 *, 2);
    var_s5 = temp_v1;
    if (temp_v1 > 0) {
loop_2:
        temp_a0 = (arg0 * 0x14) + &D_800E2970;
        temp_a1 = M2C_FIELD(temp_a0, s16 *, 0);
        temp_a0_2 = M2C_FIELD(temp_a0, s16 *, 4);
        var_s0 = temp_a1;
        var_s2 = temp_a0_2;
        var_s1 = M2C_FIELD(&D_8008333C, s32 *, 0) + (((s16) var_s3 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) * 6) + (temp_a1 * 6);
        if (temp_a0_2 > 0) {
loop_4:
            temp_v1_2 = M2C_FIELD(var_s1, u16 *, 4);
            if (!(temp_v1_2 & 0x8400) && ((temp_v1_2 & 0x300) == 0x200)) {
                temp_v0 = func_800BCB04((((s32) (var_s0 << 0x10) >> 0xA) + 0x20) & 0xFFE0, (((s16) var_s3 << 6) + 0x20) & 0xFFFF, -0x400);
                if (temp_v0 < 0x200) {
                    *arg1 = var_s0;
                    *arg2 = var_s3;
                    return temp_v0;
                }
            }
            var_s0 += 1;
            temp_v0_3 = var_s2 - 1;
            var_s2 = temp_v0_3;
            var_s1 += 6;
            if ((temp_v0_3 << 0x10) <= 0) {
                goto block_9;
            }
            goto loop_4;
        }
block_9:
        temp_v0_4 = var_s5 - 1;
        var_s5 = temp_v0_4;
        var_s3 += 1;
        if ((temp_v0_4 << 0x10) <= 0) {
            goto block_10;
        }
        goto loop_2;
    }
block_10:
    return 0x200;
}
