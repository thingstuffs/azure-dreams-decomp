#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B7D74(); /* extern */

void func_800B8024(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_s0;

    func_800B7D74(arg0, arg1, arg2, 1);
    func_800B7D74(arg0, arg1, arg2, 2);
    func_800B7D74(arg0, arg1, arg2, 3);
    func_800B7D74(arg0, arg1, arg2, 4);
    var_s0 = 0xA;
    do {
        func_800B7D74(arg0, arg1, arg2, 0);
        var_s0 -= 1;
    } while (var_s0 > 0);
    func_800A56E0(0x513);
}
