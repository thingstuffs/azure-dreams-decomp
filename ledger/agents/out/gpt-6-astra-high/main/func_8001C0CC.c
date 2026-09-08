#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Forward the target and value to func_80402F84 with selectors 0 and 1. */
void func_8001C0CC(M2C_UNK target, M2C_UNK value) {
    func_80402F84(target, 0, 1, value);
}
