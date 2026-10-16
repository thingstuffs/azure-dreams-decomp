#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

s32 townInitializeMoguraMinigame(); /* extern */
void townInitializeResourceSelectorSix();                            /* extern */

/* start_mogura_func: initialize the mogura activity and reset its four control values. */
void start_mogura_func(void) {
    townInitializeResourceSelectorSix();
    townInitializeMoguraMinigame(0, 0, 0, 0);
}
