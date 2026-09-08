#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */
M2C_UNK func_800C178C();            /* extern */

/* Invoke operation 0xD with -1, then run the two runtime routines. */
void func_8003B2C4(void) {
    func_800C178C(0xD, -1);
    func_8003B034();
    func_8003B06C();
}
