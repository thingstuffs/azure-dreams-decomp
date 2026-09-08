#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Passes value to func_80022D60 with 0x11 and two zero arguments. */
void func_8002311C(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 0x11, zero, zero);
}
