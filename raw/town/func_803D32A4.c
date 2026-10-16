#include "common.h"
#include "m2c_compat.h"

s32 func_8001A250(s32, M2C_UNK);                    /* extern */
extern M2C_UNK D_80016128;
extern M2C_UNK D_80016150;

s32 func_8001A2A4(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;

    var_s0 = arg0;
    var_s2 = 0x7FFFFFFF;
    var_s1 = 0;
    var_s3 = 0;
    if (arg2 > 0) {
        do {
            temp_v0 = func_8001A250(var_s0, arg1);
            if (temp_v0 < var_s2) {
                var_s3 = var_s0;
                var_s2 = temp_v0;
            }
            var_s1 += 1;
            var_s0 += 8;
        } while (var_s1 < arg2);
    }
    if (var_s3 == 0) {
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016128, &D_80016150, 0x40);
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
    }
    return var_s3;
}
