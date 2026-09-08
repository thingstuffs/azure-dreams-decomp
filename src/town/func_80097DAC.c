#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800954C4(s32);                            /* extern */
M2C_UNK func_800954DC();                         /* extern */
M2C_UNK func_800954F4();                         /* extern */

/* Runs the three update routines for the supplied context. */
void func_8009550C(s32 context) {
    func_800954C4(context);
    func_800954DC(context);
    func_800954F4(context);
}
