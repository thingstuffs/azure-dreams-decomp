#include "common.h"

/* 12-byte struct; entries in D_80086C00[8] */
typedef struct {
    s16 field_0;
    s16 field_2;
    s8 pad4[4];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 audio_sequence_slots[8];
extern s32 get_sequence_play_state(void);

/* Advances an entry's state from 1 to 3 when get_sequence_play_state returns 3, then returns the state. */
s16 update_sequence_slot_state(s16 entry_index)
{
    S_80086C00 *entries = audio_sequence_slots;
    S_80086C00 *entry = &entries[entry_index];

    if (entry->field_2 == 1) {
        s32 next_state = get_sequence_play_state();
        if (next_state == 3) {
            entry->field_2 = (s16)next_state;
        }
    }
    return audio_sequence_slots[entry_index].field_2;
}
