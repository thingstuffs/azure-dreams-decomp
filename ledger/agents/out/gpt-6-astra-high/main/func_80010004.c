#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Passes value, 11, and two zero arguments to func_80022D60. */
void func_80023004(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 0xb, zero, zero);
}
