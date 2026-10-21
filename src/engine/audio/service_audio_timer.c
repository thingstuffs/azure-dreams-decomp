#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* Globals accessed directly via %hi/%lo (not $gp small-data). Declared with a
 * size > -G (8) so gcc/as emit %hi/%lo rather than $gp-relative access; the
 * element type reflects the access width, the array length is provisional. */
extern int audio_timer_update_enabled[4];

/* Call open_timer_2_update_event when D_80086D4C[0] is 1 through 3, then always set D_80073824[0] to 1. */
void service_audio_timer(void)
{
    if (audio_slot_service_word[0] > 0) {
        if (audio_slot_service_word[0] < 4) {
            open_timer_2_update_event();
        }
    }
    audio_timer_update_enabled[0] = 1;
}
