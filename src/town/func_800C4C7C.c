#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80020300(); /* extern */
void func_800C23A8();                            /* extern */

/* start_keima_func: Prepare and start the keima event. */
void start_keima_func(void) {
    func_800C23A8();
    func_80020300(0, 0, 0, 0);
}
