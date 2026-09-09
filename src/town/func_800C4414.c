#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800499BC();                            /* extern */
M2C_UNK load_bin_nametwin();                            /* extern */
M2C_UNK reserve_twch_load();                     /* extern */

/* Run two setup routines, then call reserve_twch_load with mode 2. */
void func_800C1B74(void) {
    func_800499BC();
    load_bin_nametwin();
    reserve_twch_load(2);
}
