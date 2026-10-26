#include "engine/audio.h"
#include "common.h"
#include "dungeon/system.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Select buffered entry 0 in mode 1 and issue request 0x200. */
void trigger_floor_event_and_play_sound(void) {
    select_sound_stream(0, 1);
    play_sound_if_enabled(0x200);
}
