#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800179A0();                            /* extern */
extern M2C_UNK D_800190BC;

/* Calls func_800179A0 and returns the address of D_800190BC. */
M2C_UNK *func_806974BC(void) {
    func_800179A0();
    return &D_800190BC;
}
