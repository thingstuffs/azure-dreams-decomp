#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/entity.h"

/* Optionally lowers the note by 0x18, clamps it, and stores it in both note fields. */
void set_playback_note(s32 note) {
    s32 clamped_note;

    sound_sequence_task.fade_target = (s16) note;
    if (((s32)sound_playback_state.flags00) & 0x20) {
        sound_sequence_task.fade_target = (s16) (note - 0x18);
    }
    clamped_note = clamp_sound_value_to_seven_bits(sound_sequence_task.fade_target);
    sound_sequence_task.fade_target = (s16) clamped_note;
    sound_sequence_task.fade_level = (s16) clamped_note;
}
