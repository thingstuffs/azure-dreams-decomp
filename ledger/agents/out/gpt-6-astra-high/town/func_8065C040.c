#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80018250;
extern M2C_UNK *D_800183E8;

/* Point D_800183E8 at D_80018250. */
void func_8065C040(void) {
    D_800183E8 = &D_80018250;
}
