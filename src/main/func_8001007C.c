#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forwards the value to func_80022D60 with mode 3 and zeroed trailing arguments. */
void func_8002307C(s32 value) {
    s32 zero = 0;
    func_80022D60(value, 3, zero, zero);
}
