#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80020298();                            /* extern */
void finalize_town_resource_operation();                            /* extern */

/* Run the two handlers for town script call 100. */
void scr_func_sn_casino(void) {
    finalize_town_resource_operation();
    func_80020298();
}
