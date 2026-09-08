#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Passes value to func_80402F84 with fixed arguments 0x10, 0, 0. */
void func_8001C34C(M2C_UNK value) {
    func_80402F84(value, 0x10, 0, 0);
}
