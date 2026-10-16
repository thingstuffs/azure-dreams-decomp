#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeResourceSelectorSix();                            /* extern */

/* Run func_sn_ball initialization and reset the four control values. */
void scr_func_sn_ball(void) {
    townInitializeResourceSelectorSix();
    townInitializeSnowballMinigame(0, 0, 0, 0);
}
