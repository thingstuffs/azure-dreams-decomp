#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800190F0;
extern M2C_UNK *D_80019270;

/* Point D_80019270 at D_800190F0. */
void func_80016DF0(void) {
    D_80019270 = &D_800190F0;
}
