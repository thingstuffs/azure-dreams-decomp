#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Calls func_80022D60 with selector 9 and two zero arguments. */
void func_80022FB4(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 9, zero, zero);
}
