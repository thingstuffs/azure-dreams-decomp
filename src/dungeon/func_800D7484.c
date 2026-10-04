#include "common.h"
#include "m2c_compat.h"

void func_800DBE98();                            /* extern */
s32 func_800DCA1C();                    /* extern */
void func_800DCA88(s32 *, s32);                            /* extern */
void func_800DCAC4();              /* extern */

/* Run both setup calls, compute the result from the pointed value, and finalize. */
s32 func_800DCBE4(s32 *value_ptr, s32 context) {
    s32 result;

    func_800DCA88(value_ptr, context);
    func_800DCAC4(value_ptr, context);
    result = func_800DCA1C(*value_ptr, context);
    func_800DBE98();
    return result;
}
