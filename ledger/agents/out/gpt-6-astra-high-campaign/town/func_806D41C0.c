#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800177CC();                /* extern */
M2C_UNK func_8001860C();                     /* extern */

/* Calls the setup handler with 0x98F, then forwards the arguments. */
void func_806D41C0(s32 value, M2C_UNK context) {
    func_8001860C(0x98F);
    func_800177CC(value, context);
}
