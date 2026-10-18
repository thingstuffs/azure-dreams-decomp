#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 set_hold_item_callback(); /* extern */

/* ext_plsel_hold_item_set: set the selected player's held item. */
void ext_plsel_hold_item_set(void) {
    set_hold_item_callback(0, 0, 0, 0);
}
