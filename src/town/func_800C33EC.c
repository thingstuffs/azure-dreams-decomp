#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 townSetReturnItemCallback(); /* extern */

/* ext_plsel_kaesu_set: call townSetReturnItemCallback with all four arguments cleared. */
void ext_plsel_kaesu_set(void) {
    townSetReturnItemCallback(0, 0, 0, 0);
}
