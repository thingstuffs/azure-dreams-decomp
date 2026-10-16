#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E2970;

s16 func_80017EBC(s16 arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 var_a0;
    s16 var_a1;
    s16 var_a3;
    u16 var_a2;
    void *temp_v1;
    void *var_v1;

    var_a1 = 0;
    temp_v1 = (arg0 * 0x14) + &D_800E2970;
    temp_v0 = M2C_FIELD(temp_v1, s16 *, 6);
    var_a2 = M2C_FIELD(temp_v1, u16 *, 2);
    var_a3 = temp_v0;
    if (temp_v0 > 0) {
        do {
            temp_v0_3 = M2C_FIELD(temp_v1, s16 *, 4);
            var_v1 = M2C_FIELD(&D_8008333C, s32 *, 0) + (((s16) var_a2 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) * 6) + (M2C_FIELD(temp_v1, u16 *, 0) * 6);
            var_a0 = temp_v0_3;
            if (temp_v0_3 > 0) {
                do {
                    temp_v0_4 = var_a0 - 1;
                    if (!(M2C_FIELD(var_v1, u16 *, 4) & 0x8500)) {
                        var_a1 += 1;
                    }
                    var_a0 = temp_v0_4;
                    var_v1 += 6;
                } while ((temp_v0_4 << 0x10) > 0);
            }
            temp_v0_2 = var_a3 - 1;
            var_a3 = temp_v0_2;
            var_a2 += 1;
        } while ((temp_v0_2 << 0x10) > 0);
    }
    return var_a1;
}
