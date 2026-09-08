#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forward the target and value to func_80022D60 with fixed parameters 6 and 2. */
void func_80022F64(M2C_UNK target, M2C_UNK value) {
    func_80022D60(target, 6, 2, value);
}
