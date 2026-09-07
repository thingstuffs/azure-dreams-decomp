#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8002290C();                         /* extern */
M2C_UNK func_80022A30();                    /* extern */

void func_80022AE8(s32 arg0) {
    func_80022A30(arg0 + 0x24, arg0);
    func_8002290C(arg0);
}
