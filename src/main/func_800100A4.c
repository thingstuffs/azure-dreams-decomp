#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Passes the value and fixed arguments (7, 0, 0) to func_80022D60. */
void func_800230A4(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 7, zero, zero);
}
