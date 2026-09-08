#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Forwards the target to func_80402F84 with fixed arguments 0x11, 0, and 0. */
void func_8001C374(M2C_UNK target) {
    func_80402F84(target, 0x11, 0, 0);
}
