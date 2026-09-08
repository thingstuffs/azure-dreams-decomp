#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009CEE8();                            /* extern */
M2C_UNK func_800A496C();                            /* extern */

/* Runs func_8009CEE8 followed by func_800A496C. */
void func_8009CE80(void) {
    func_8009CEE8();
    func_800A496C();
}
