#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018C74(M2C_UNK);                     /* extern */
M2C_UNK func_80018CEC(M2C_UNK);                     /* extern */
s32 func_80018D6C(M2C_UNK);                         /* extern */

s32 func_80016D40(void) {
    s32 var_v0;

    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    var_v0 = 0;
    if (func_80018D6C(0x7D1) != 0) {
        var_v0 = 0;
        if (func_80018D6C(0x7D2) == 0) {
            var_v0 = 0;
            if (func_80018D6C(0xFC6) != 0) {
                func_80018C74(0x7D5);
                var_v0 = 1;
            }
        }
    }
    return var_v0;
}
