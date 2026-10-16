#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8001B688;

/* Returns the address of D_8001B688. */
M2C_UNK *townGetDataPointer1B688(void) {
    return &D_8001B688;
}
