#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeResourceSelectorSix();                            /* extern */

/* Run start_tako_func initialization and reset the four control values. */
void start_tako_func(void) {
    townInitializeResourceSelectorSix();
    townInitializeTakoMinigame(0, 0, 0, 0);
}
