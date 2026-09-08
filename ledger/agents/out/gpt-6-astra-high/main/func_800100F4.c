#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forwards value to func_80022D60 with code 0x10 and two zero arguments. */
void func_800230F4(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 0x10, zero, zero);
}
