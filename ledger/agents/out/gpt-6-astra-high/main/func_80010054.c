#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forwards the input value with 0xD and two zero arguments to func_80022D60. */
void func_80023054(s32 input_value) {
    s32 zero = 0;
    func_80022D60(input_value, 0xd, zero, zero);
}
