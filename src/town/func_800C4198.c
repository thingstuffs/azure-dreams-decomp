#include "common.h"
#include "m2c_compat.h"

M2C_UNK reserve_twch_load();                     /* extern */

/* Calls reserve_twch_load for IDs 6 and 3. */
void func_800C18F8(void) {
    reserve_twch_load(6);
    reserve_twch_load(3);
}
