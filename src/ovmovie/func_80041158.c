#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8006005C();                /* extern */

/* Forwards the value to func_8006005C with a zero first argument. */
void func_80041158(s32 value) {
    func_8006005C(0, value);
}
