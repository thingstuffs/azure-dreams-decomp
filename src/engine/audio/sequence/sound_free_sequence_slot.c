#include "common.h"
#include "slus/audio_update_guard_data.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"

/* S_80086C00: 12-byte-stride sound-driver "sequence slot" table (8 entries),
 * indexed by the slot index arg0. Canonical layout established by sibling
 * functions (w_8005AE08.c, w_8005AE90.c, w_8005B27C.c, w_8005C5D0.c). */


/* Resets a sound sequence slot to its free/default state. */
void sound_free_sequence_slot(s32 slot_id)
{
    s16 slot_index;

    audio_update_guard.value = 1;
    reset_sequence_track_state();
    audio_reset_sequence_tracks_and_channels();
    slot_index = (s16)slot_id;

    audio_sequence_slots[slot_index].sequence_id = -1;
    audio_sequence_slots[slot_index].state = 0;
    audio_sequence_slots[slot_index].right_gain = 0x7F;
    audio_sequence_slots[slot_index].left_gain = 0x7F;

    audio_update_guard.value = 0;
}
