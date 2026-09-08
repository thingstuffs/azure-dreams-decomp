#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001922C();                /* extern */

/* Forwards the base value plus four to func_8001922C with mode 1. */
void func_80019308(s32 base_value) {
    func_8001922C(base_value + 4, 1);
}
