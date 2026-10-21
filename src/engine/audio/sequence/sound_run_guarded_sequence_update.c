#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

typedef struct {
    s32 v;
    s32 pad[2];
} S_80085F98;

extern S_80085F98 audio_update_guard;
extern s32 audio_sequence_active[];
extern s32 audio_sequence_timing_division[];

/* Prevents re-entry while processing active state updates and running cleanup. */
void sound_run_guarded_sequence_update(void) {
    if (audio_update_guard.v == 0) {
        audio_update_guard.v = 1;
        if (audio_sequence_active[0] != 0) {
            if (audio_sequence_timing_division[0] == 0x1E0) {
                tick_enabled_sequence_tracks();
                tick_enabled_sequence_tracks();
                tick_enabled_sequence_tracks();
                tick_enabled_sequence_tracks();
                tick_enabled_sequence_tracks();
                tick_enabled_sequence_tracks();
            }
            tick_enabled_sequence_tracks();
            tick_enabled_sequence_tracks();
            tick_enabled_sequence_tracks();
            tick_enabled_sequence_tracks();
        }
        sound_update_voice_modulation_slots();
        drain_ready_sound_voice_flags();
        audio_update_guard.v = 0;
    }
}
