#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Calls func_80022D60 with the supplied value, 10, and two zero arguments. */
void func_80022FDC(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 0xa, zero, zero);
}
