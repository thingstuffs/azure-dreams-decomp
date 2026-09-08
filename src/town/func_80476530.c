#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80016400;

/* Returns the address of D_80016400. */
M2C_UNK *func_80017530(void) {
    return &D_80016400;
}
