#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_80017480(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s16 var_a1;
    s16 var_a3;
    s32 temp_t0;
    s32 temp_v1;
    u16 temp_v0;
    void *temp_v1_2;

    var_a1 = arg1;
    temp_v1 = var_a1 + arg3;
    if (var_a1 < temp_v1) {
        do {
            var_a3 = arg0;
            if (var_a3 < (var_a3 + arg2)) {
                temp_t0 = var_a3 + arg2;
                do {
                    temp_v1_2 = ((var_a3 + (var_a1 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + &D_800EA000;
                    temp_v0 = M2C_FIELD(temp_v1_2, u16 *, 4);
                    var_a3 += 1;
                    M2C_FIELD(temp_v1_2, s16 *, 4) = (s16) (temp_v0 & arg4);
                } while (var_a3 < temp_t0);
            }
            var_a1 += 1;
        } while (var_a1 < temp_v1);
    }
}
