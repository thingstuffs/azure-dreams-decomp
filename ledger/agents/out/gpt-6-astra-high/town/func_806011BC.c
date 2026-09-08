#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017DD4();                     /* extern */

/* Calls func_80017DD4 with 0xFA3 and returns zero. */
s32 func_806011BC(void) {
    func_80017DD4(0xFA3);
    return 0;
}
