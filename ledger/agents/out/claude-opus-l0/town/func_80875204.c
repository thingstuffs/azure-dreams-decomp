#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700C08();                     /* extern */
M2C_UNK func_80701060();                            /* extern */
M2C_UNK func_8070114C();                            /* extern */

/* Devkit flag-test entry: select page 0, redraw the grid, then run the flag scan. */
s32 func_80875204(void) {
    func_80700C08(0);
    func_8070114C();
    func_80701060();
    return 0;
}
