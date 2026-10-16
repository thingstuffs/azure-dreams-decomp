#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700188(M2C_UNK);                     /* extern */
M2C_UNK func_80700590();                            /* extern */
M2C_UNK func_80700674();                            /* extern */

s32 func_80700724(void) {
    func_80700188(0);
    func_80700674();
    func_80700590();
    return 0;
}
