#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800DBE98();                            /* extern */
s32 func_800DCA1C();                    /* extern */
M2C_UNK func_800DCA88();                            /* extern */
M2C_UNK func_800DCAC4();              /* extern */

s32 func_800DCBE4(s32 *arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_800DCA88();
    func_800DCAC4(arg0, arg1);
    temp_s0 = func_800DCA1C(*arg0, arg1);
    func_800DBE98();
    return temp_s0;
}
