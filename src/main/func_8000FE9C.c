#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Initialize the context in mode 1 with zero optional arguments. */
void func_80022E9C(s32 context) {
    s32 zero = 0;
    func_80022D60(context, 1, zero, zero);
}
