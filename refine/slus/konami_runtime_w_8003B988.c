#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B64C();                            /* extern */
M2C_UNK func_8003B8DC();                            /* extern */
M2C_UNK func_80043458();                            /* extern */

/* Runs the three runtime routines in sequence. */
void func_8003B988(void) {
    func_80043458();
    func_8003B64C();
    func_8003B8DC();
}
