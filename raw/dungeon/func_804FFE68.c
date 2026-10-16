#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

void func_80017668(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4) {
    s16 var_a1;
    s16 var_a3;
    s16 var_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_t2;

    var_a1 = arg1;
    var_t2 = arg3;
    if ((arg3 << 0x10) > 0) {
        do {
            var_a3 = arg2;
            var_t0 = arg0;
            if (var_a3 > 0) {
                do {
                    var_a3 -= 1;
                    temp_v1 = (var_a1 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_t0;
                    var_t0 += 1;
                    M2C_FIELD(((temp_v1 * 6) + &D_800EA000), u16 *, 4) = arg4;
                } while (var_a3 > 0);
            }
            temp_v0 = var_t2 - 1;
            var_t2 = temp_v0;
            var_a1 += 1;
        } while ((temp_v0 << 0x10) > 0);
    }
}
