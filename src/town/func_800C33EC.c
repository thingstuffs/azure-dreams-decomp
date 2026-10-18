#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 set_return_item_callback(); /* extern */

/* ext_plsel_kaesu_set: call set_return_item_callback with all four arguments cleared. */
void ext_plsel_kaesu_set(void) {
    set_return_item_callback(0, 0, 0, 0);
}
