#include "modules/town_minigame_dispatch.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80020300(s32, s32, s32, s32);
void finalize_keima_resource_operation();                            /* extern */

/* start_keima_func: Prepare and start the keima event. */
void start_keima_func(void) {
    finalize_keima_resource_operation();
    func_80020300(0, 0, 0, 0);
}
