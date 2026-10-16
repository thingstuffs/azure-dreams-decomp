#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016024;
extern M2C_UNK D_8001604C;

s32 func_80016514(void *arg0, s32 arg1) {
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;

    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 8) != 0) {
        var_v0 = 0 * 8;
loop_2:
        var_v0_2 = var_s1 * 8;
        if (*(((var_v0 - var_s1) * 4) + arg0) != arg1) {
            var_s1 += 1;
            var_v0 = var_s1 * 8;
            if (M2C_FIELD(((var_s1 * 0x1C) + arg0), s32 *, 8) == 0) {
                goto block_4;
            }
            goto loop_2;
        }
    } else {
block_4:
        var_v0_2 = var_s1 * 8;
    }
    if (M2C_FIELD((((var_v0_2 - var_s1) * 4) + arg0), s32 *, 8) == 0) {
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_80016024, &D_8001604C, 0x37);
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
    }
    return var_s1;
}
