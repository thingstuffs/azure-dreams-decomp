#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Starts mode 8 for the owner with no additional parameters. */
void func_80022EEC(s32 owner) {
    func_80022D60(owner, 8, 0, 0);
}
