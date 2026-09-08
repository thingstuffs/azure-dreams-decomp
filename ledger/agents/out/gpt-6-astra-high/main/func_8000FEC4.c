#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Forwards the input and value with both middle arguments set to 2. */
void func_80022EC4(M2C_UNK input, M2C_UNK value) {
    func_80022D60(input, 2, 2, value);
}
