#include "common.h"
#include "m2c_compat.h"

void func_800954C4(s32);                            /* extern */
void func_800954DC();                         /* extern */
void func_800954F4();                         /* extern */

/* Runs the three update routines for the supplied context. */
void func_8009550C(s32 context) {
    func_800954C4(context);
    func_800954DC(context);
    func_800954F4(context);
}
