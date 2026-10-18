#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

s32 initialize_mogura_minigame(); /* extern */
void initialize_resource_selector_six();                            /* extern */

/* start_mogura_func: initialize the mogura activity and reset its four control values. */
void start_mogura_func(void) {
    initialize_resource_selector_six();
    initialize_mogura_minigame(0, 0, 0, 0);
}
