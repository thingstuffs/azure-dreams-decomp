#include "common.h"
#include "dungeon/system.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Call play_sound_if_enabled with ID 0x2D1. */
void play_floor_event_sound(void) {
    play_sound_if_enabled(0x2D1);
}
