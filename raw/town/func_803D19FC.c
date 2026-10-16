#include "common.h"
#include "m2c_compat.h"

s32 func_800189FC(void *arg0, s32 arg1) {
    s32 (*var_v0)(void *);
    s32 var_s1;
    void *var_s0;

    var_s0 = arg0;
    var_s1 = 0;
    if (M2C_FIELD(var_s0, u8 *, 1) != 0) {
        do {
            if (M2C_FIELD(var_s0, u8 *, 3) & 0x20) {
                if (arg1 == 0) {
                    var_v0 = M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), s32 (**)(void *), 0x50);
                } else {
                    var_v0 = M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), s32 (**)(void *), 0x6C);
                }
                var_s1 += var_v0(var_s0);
            }
            var_s0 += 4;
        } while (M2C_FIELD(var_s0, u8 *, 1) != 0);
    }
    return var_s1;
}
