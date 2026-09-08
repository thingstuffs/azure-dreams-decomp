#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A7B98(s32, M2C_UNK, M2C_UNK);                            /* extern */
M2C_UNK func_800C3FFC();       /* extern */

/* Run both object handlers with the supplied state and context. */
void func_800C885C(s32 object, M2C_UNK state, M2C_UNK context) {
    func_800A7B98(object, state, context);
    func_800C3FFC(object, state, context);
}
