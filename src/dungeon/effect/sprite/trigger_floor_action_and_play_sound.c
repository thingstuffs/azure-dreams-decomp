#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 play_sound_if_enabled();                     /* extern */

/* Selects buffered entry 0x2A in mode 1, then dispatches request 0x200. */
void trigger_floor_action_42_and_play_sound(void) {
    select_sound_stream(0x2A, 1);
    play_sound_if_enabled(0x200);
}
