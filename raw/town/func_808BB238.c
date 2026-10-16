#include "common.h"
#include "m2c_compat.h"

s32 func_80000C6C(u16);                             /* extern */

void func_80000A38(void) {
    void *var_s0;
    void *var_s1;

    var_s1 = NULL;
    var_s0 = NULL;
loop_1:
    var_s0 += 4;
    if (func_80000C6C(M2C_FIELD(var_s0, u16 *, 0xF28)) != 0) {
        var_s1 += 1;
        goto loop_1;
    }
    M2C_FIELD((M2C_FIELD(var_s1, s8 *, 0xFBC) * 4), M2C_UNK (**)(void *), 0xFB4)(var_s1);
}
