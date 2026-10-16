#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeResourceSelectorSix();                            /* extern */

/* start_gym_func: Prepare and start the gym event. */
void start_gym_func(void) {
    townInitializeResourceSelectorSix();
    townInitializeGymMinigame(0, 0, 0, 0);
}
