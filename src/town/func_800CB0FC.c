#include "common.h"
#include "m2c_compat.h"

void func_800A7B98(s32, s32, s32);                            /* extern */
void func_800C3FFC();       /* extern */

/* Run both object handlers with the supplied state and context. */
void func_800C885C(s32 object, s32 state, s32 context) {
    func_800A7B98(object, state, context);
    func_800C3FFC(object, state, context);
}
