#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800499BC();                            /* extern */
M2C_UNK func_8004B834();                            /* extern */
M2C_UNK func_8008B408();                     /* extern */

/* Run two setup routines, then call func_8008B408 with mode 2. */
void func_800C1B74(void) {
    func_800499BC();
    func_8004B834();
    func_8008B408(2);
}
