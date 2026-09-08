#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800BBC1C();                     /* extern */
M2C_UNK func_800CC384();       /* extern */

/* Prepare the context and forward the arguments to the next handler. */
void func_800CC330(s32 object, M2C_UNK context, M2C_UNK callback_arg) {
    func_800BBC1C(context);
    func_800CC384(object, context, callback_arg);
}
