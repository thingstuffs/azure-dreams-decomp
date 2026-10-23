#include "common.h"
#include "engine/audio/sequence.h"

/* 12-byte struct; entries in D_80086C00[8] */

extern SoundSequenceSlot audio_sequence_slots[8];

/* Advances an entry's state from 1 to 3 when get_sequence_play_state returns 3, then returns the state. */
s16 update_sequence_slot_state(s16 entry_index)
{
    SoundSequenceSlot *entries = audio_sequence_slots;
    SoundSequenceSlot *entry = &entries[entry_index];

    if (entry->state == 1) {
        s32 next_state = get_sequence_play_state();
        if (next_state == 3) {
            entry->state = (s16)next_state;
        }
    }
    return audio_sequence_slots[entry_index].state;
}
