#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

void func_80022EC4(M2C_UNK arg0, M2C_UNK arg1) {
    M2C_UNK orig = arg1;
    arg1 = 2;
    func_80022D60(arg0, arg1, arg1, orig);
}
