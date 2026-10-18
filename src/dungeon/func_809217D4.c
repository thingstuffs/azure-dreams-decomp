#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 play_sound_if_enabled();                     /* extern */

/* Call play_sound_if_enabled with ID 0x2D1. */
void play_floor_event_sound(void) {
    play_sound_if_enabled(0x2D1);
}
