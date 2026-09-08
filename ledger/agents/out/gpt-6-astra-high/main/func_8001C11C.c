#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80402F84();   /* extern */

/* Forwards the target and value to func_80402F84 with both selectors set to 2. */
void func_8001C11C(M2C_UNK target, M2C_UNK value) {
    func_80402F84(target, 2, 2, value);
}
