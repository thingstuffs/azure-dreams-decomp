#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8000093C(s32);                         /* extern */
s32 func_80000BE4(u16);                             /* extern */

void func_800009D4(void) {
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = NULL;
loop_1:
    var_s0 += 4;
    if (func_80000BE4(M2C_FIELD(var_s0, u16 *, 0xDB4)) != 0) {
        var_s1 += 1;
        goto loop_1;
    }
    func_8000093C(var_s1);
}
