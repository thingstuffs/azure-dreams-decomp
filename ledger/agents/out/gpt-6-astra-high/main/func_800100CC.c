#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Initialize the owner's request with type 0xf, mode 2, and its data. */
void func_800230CC(M2C_UNK owner, M2C_UNK data) {
    func_80022D60(owner, 0xf, 2, data);
}
