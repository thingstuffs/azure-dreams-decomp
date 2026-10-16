#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8001919C;
extern M2C_UNK D_800191C4;

s32 func_8001D450(void *arg0, s32 arg1) {
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;

    var_s1 = 0;
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        var_v0_2 = 0 * 8;
loop_2:
        var_v0_2 = var_s1 * 8;
        if (*(var_v0_2 + arg0) != arg1) {
            var_s1 += 1;
            var_v0_2 = var_s1 * 8;
            if (M2C_FIELD(((var_s1 * 8) + arg0), s32 *, 4) != 0) {
                goto loop_2;
            }
        }
        var_v0 = var_s1;
        if (M2C_FIELD((var_v0_2 + arg0), s32 *, 4) == 0) {
            goto block_5;
        }
    } else {
block_5:
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *, M2C_UNK *, M2C_UNK), 0x168)(&D_8001919C, &D_800191C4, 0x28);
        M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x174)(1);
        var_v0 = var_s1;
    }
    return var_v0;
}
