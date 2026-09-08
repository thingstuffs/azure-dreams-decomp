#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forwards the value to func_80022D60 with code 12 and two zero arguments. */
void func_8002302C(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 0xc, zero, zero);
}
