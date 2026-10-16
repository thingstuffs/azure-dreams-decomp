#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80020298();                            /* extern */
void townFinalizeTownResourceOperation();                            /* extern */

/* Run the two handlers for town script call 100. */
void scrFuncSnCasino(void) {
    townFinalizeTownResourceOperation();
    func_80020298();
}
