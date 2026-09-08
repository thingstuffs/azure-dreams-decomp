#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Initialize a type-5, mode-1 context with the supplied owner and data. */
void func_80022F3C(M2C_UNK owner, M2C_UNK data) {
    func_80022D60(owner, 5, 1, data);
}
