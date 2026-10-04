#include "common.h"
#include "m2c_compat.h"

s32 func_800BBC1C();                     /* extern */
void func_800CC384();       /* extern */

/* Prepare the context and forward the arguments to the next handler. */
void func_800CC330(s32 object, s32 context, s32 callback_arg) {
    func_800BBC1C(context);
    func_800CC384(object, context, callback_arg);
}
