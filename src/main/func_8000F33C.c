#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E264();                /* extern */
M2C_UNK func_8004E884();                     /* extern */

void func_8002233C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;
    s32 var_s1;

    func_8004E884(arg0, 1);
    var_s1 = arg0 + (arg1 * 0xC);
    var_s0 = 0;
    if (arg2 > 0) {
        do {
            func_8004E264(var_s1, 0);
            var_s0 += 1;
            var_s1 += 0xC;
        } while (var_s0 < arg2);
    }
}
