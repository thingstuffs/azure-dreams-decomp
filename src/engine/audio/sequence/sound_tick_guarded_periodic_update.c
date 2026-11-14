#include "common.h"
#include "slus/audio_update_guard_data.h"
#include "slus/audio_timer_update_enabled_data.h"
#include "engine/audio/sequence.h"
#include "slus.h"

typedef struct {
    s32 v;
    s32 pad[2];
} PaddedS32;

extern PaddedS32 audio_maintenance_ticks;

/* Runs an enabled update with a reentry guard and periodic maintenance. */
long long sound_tick_guarded_periodic_update(void)
{
    s32 update_enabled;

    update_enabled = audio_timer_update_enabled.value;
    if ((update_enabled != 0) && (audio_update_guard.value == 0)) {
        audio_update_guard.value = 1;
        tick_enabled_sequence_tracks();
        if (audio_maintenance_ticks.v >= 11) {
            sound_update_voice_modulation_slots();
            drain_ready_sound_voice_flags();
            audio_maintenance_ticks.v = 0;
        }
        audio_update_guard.value = 0;
        audio_maintenance_ticks.v += 1;
    }
}
