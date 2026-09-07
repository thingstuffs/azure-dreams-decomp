#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */
M2C_UNK func_800903A8();                            /* extern */

/* Runs the three runtime routines in sequence. */
void func_8003B1B4(void) {
    func_8003B034();
    func_8003B06C();
    func_800903A8();
}
