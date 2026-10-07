#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800C23A8();                            /* extern */

/* start_keima2_func: Prepare and start the second keima event. */
void start_keima2_func(void) {
    func_800C23A8();
    func_800212B8(0, 0, 0, 0);
}
