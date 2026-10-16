#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8008333C;
extern M2C_UNK D_800EA000;

s16 func_80017584(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 var_a1;
    s16 var_a3;
    s16 var_t0;
    s16 var_t1;
    s16 var_v0;
    u16 temp_v0;

    var_a1 = arg1;
    var_v0 = -1;
    if (var_a1 > 0) {
        if (arg0 > 0) {
            var_v0 = -1;
            if ((var_a1 + arg3) < (1 << M2C_FIELD(&D_8008333C, s16 *, 0x16))) {
                var_t1 = arg3;
                if ((arg0 + arg2) >= (1 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) {
                    goto block_4;
                }
                if (var_t1 > 0) {
loop_8:
                    var_a3 = arg2;
                    var_t0 = arg0;
                    if (var_a3 > 0) {
loop_10:
                        temp_v0 = M2C_FIELD(((((var_a1 << M2C_FIELD(&D_8008333C, s16 *, 0x14)) + var_t0) * 6) + &D_800EA000), u16 *, 4);
                        var_a3 -= 1;
                        if (temp_v0 == 0) {
                            var_t0 += 1;
                            if (var_a3 <= 0) {
                                goto block_12;
                            }
                            goto loop_10;
                        }
                        return (s16) temp_v0;
                    }
block_12:
                    var_t1 -= 1;
                    var_a1 += 1;
                    if (var_t1 <= 0) {
                        goto block_13;
                    }
                    goto loop_8;
                }
block_13:
                var_v0 = 0;
                /* Duplicate return node #14. Try simplifying control flow for better match */
                return var_v0;
            }
            /* Duplicate return node #14. Try simplifying control flow for better match */
            return var_v0;
        }
block_4:
        return -1;
    }
    return var_v0;
}
