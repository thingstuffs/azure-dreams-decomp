#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"
#include "slus.h"
#include "slus/data.h"
#include "engine/audio/slots.h"

extern void *audio_selection_record_pointers[][16];

/* Starts playback of the pending selection when available and initializes its mode. */
void start_pending_selection(void)
{
    u8 entry_data[32];
    s16 note_offset;
    u16 selection;
    s16 entry_index;
    s16 entry_value;
    u16 mode_bits;
    s16 is_ready;

    if (sound_playback_state.unk_26 == -1) {
        handle_audio_status_code(0x71);
        return;
    }
    is_ready = test_sound_channel_availability(0);
    if (!is_ready) {
        sound_playback_state.flags04 |= 2;
        return;
    }
    note_offset = -((((u8)sound_playback_state.unk_26) >> 4) << 1);
    if (copy_sound_slot_info(0, entry_data) == 0) {
        set_playback_note(entry_data[0x18] + note_offset);
    } else {
        set_playback_note(0x64);
    }

    selection = sound_playback_state.unk_26;
    mode_bits = selection & 0xF000;
    entry_index = selection & 0xF;
    sound_playback_state.unk_26 = entry_index;
    entry_value = pending_sound_selection_entries[((u16)sound_playback_state.unk_20)][entry_index];
    if (entry_value != 0) {
        submit_shifted_stereo_sound_parameters(entry_value, entry_value);
    }
    sound_playback_state.unk_22 = allocate_sequence_bank_slot(
        audio_selection_record_pointers[((u16)sound_playback_state.unk_20)][sound_playback_state.unk_26], 0);
    sound_playback_state.unk_26 = -1;
    sound_playback_state.flags00 &= ~0x1000;
    sound_playback_state.flags04 &= ~2;
    if (mode_bits != 0) {
        sound_sequence_task.unk_04 = 1;
        sound_sequence_task.unk_08 = 0;
        switch (mode_bits) {
        case 0x9000:
            sound_sequence_task.unk_16 = 4;
            break;
        case 0x8000:
            sound_sequence_task.unk_16 = 2;
            break;
        default:
            sound_sequence_task.unk_16 = 0xA;
            break;
        }
    } else {
        audio_sequence_task_phase[0] = 3;
    }
    sound_playback_state.flags00 |= 0x100;
    apply_scaled_sound_slot_volume();
    sound_activate_loaded_sequence_slot(sound_playback_state.unk_22, 1, 1);
}
