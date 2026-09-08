#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017480(); /* extern */

/* Call func_80017480 for a 64-by-64 region at the origin with value zero. */
void func_80017530(void) {
    func_80017480(0, 0, 0x40, 0x40, 0);
}
