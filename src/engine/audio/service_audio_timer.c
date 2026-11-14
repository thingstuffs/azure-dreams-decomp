#include "common.h"
#include "slus/audio_timer_update_enabled_data.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* Updates timer 2 for audio slot service states 1 through 3, then enables audio timer updates. */
void service_audio_timer(void)
{
    if (audio_slot_service_word[0] > 0) {
        if (audio_slot_service_word[0] < 4) {
            open_timer_2_update_event();
        }
    }
    audio_timer_update_enabled.value = 1;
}
