#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E9FFA;

void func_8001DC34(void *arg0) {
    s16 *var_v1;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_a1;
    s32 var_v0;
    void *var_a0;

    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    temp_v0 = M2C_FIELD(arg0, u16 *, 2) - 1;
    var_a2 = temp_v0;
    temp_v1 = temp_v0 + M2C_FIELD(arg0, u16 *, 6) + 2;
    if ((temp_v0 << 0x10) < (temp_v1 << 0x10)) {
        var_v0 = var_a2 << 0x10;
        do {
            temp_v0_3 = M2C_FIELD(arg0, u16 *, 4) + 2;
            var_a1 = temp_v0_3;
            var_v1 = ((((var_v0 >> 0x10) << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + M2C_FIELD(arg0, u16 *, 0)) * 6) + &D_800E9FFA;
            if ((temp_v0_3 << 0x10) > 0) {
                var_a0 = var_v1 + 4;
                do {
                    temp_v0_4 = var_a1 - 1;
                    var_a1 = temp_v0_4;
                    *var_v1 = 0;
                    M2C_FIELD(var_a0, s16 *, -2) = 0;
                    M2C_FIELD(var_a0, s16 *, 0) = 0;
                    var_a0 += 6;
                    var_v1 += 6;
                } while ((temp_v0_4 << 0x10) > 0);
            }
            temp_v0_2 = var_a2 + 1;
            var_a2 = temp_v0_2;
            var_v0 = var_a2 << 0x10;
        } while (temp_v0_2 < temp_v1);
    }
}
