#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void finalize_town_resource_operation();                            /* extern */

/* func_sn_casino_slot: prepare and run the casino slot event. */
void scr_func_sn_casino_slot(void) {
    finalize_town_resource_operation();
    create_minigame_display_objects();
}
