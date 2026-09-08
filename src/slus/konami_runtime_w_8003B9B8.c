#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B7C8();                            /* extern */
M2C_UNK func_8003B8DC();                            /* extern */
M2C_UNK func_80043458();                            /* extern */

/* Runs the three Konami runtime routines in sequence. */
void func_8003B9B8(void) {
    func_80043458();
    func_8003B8DC();
    func_8003B7C8();
}
