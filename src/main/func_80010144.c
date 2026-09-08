#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Initialize operation 0x12 for the owner with the supplied data. */
void func_80023144(M2C_UNK owner, M2C_UNK data) {
    func_80022D60(owner, 0x12, 1, data);
}
