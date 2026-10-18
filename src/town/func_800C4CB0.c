#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void finalize_keima_resource_operation();                            /* extern */

/* start_keima2_func: Prepare and start the second keima event. */
void start_keima2_func(void) {
    finalize_keima_resource_operation();
    initialize_keima_interface(0, 0, 0, 0);
}
