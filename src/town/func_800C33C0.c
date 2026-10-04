#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80093C40(); /* extern */

/* ext_plsel_hold_item_set: set the selected player's held item. */
void ext_plsel_hold_item_set(void) {
    func_80093C40(0, 0, 0, 0);
}
