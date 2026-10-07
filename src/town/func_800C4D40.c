#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800C2444();                            /* extern */

/* func_sn_casino_slot: prepare and run the casino slot event. */
void scr_func_sn_casino_slot(void) {
    func_800C2444();
    func_800224E0();
}
