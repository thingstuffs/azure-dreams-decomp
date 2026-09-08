#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */

/* Runs the two Konami runtime routines in sequence. */
void func_8003B210(void) {
    func_8003B034();
    func_8003B06C();
}
