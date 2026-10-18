#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls play_sound_if_enabled with the fixed argument 0xB4. */
void func_800F7BA0(void) {
    play_sound_if_enabled(0xB4);
}
