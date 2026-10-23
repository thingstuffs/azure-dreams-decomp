#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"

/* S_80086C00: 12-byte-stride entry table (8 entries), indexed by the
 * slot index arg0. field_0/field_2 are s16, field_4 is a s32 data
 * pointer, field_8/field_A are u16 (accessed here). */
 /* size 0xC (12) */

extern SoundSequenceSlot audio_sequence_slots[8];
extern s32 audio_sequence_active[4]; /* forced hi/lo access via size > 8 */
extern s32 audio_update_guard[4]; /* forced hi/lo access via size > 8 */

/* Resets sound driver state and restores the selected sequence slot to idle defaults. */
void sound_reset_sequence_slot_to_idle(s16 slot_index)
{
    SoundSequenceSlot *slots;
    int zero;

    audio_update_guard[0] = 1;
    zero = 0;
    audio_sequence_active[0] = zero;
    activate_entries_and_clear_state();
    audio_reset_sequence_tracks_and_channels();
    slots = audio_sequence_slots;
    slots[slot_index].right_gain = 0x7F;
    slots[slot_index].left_gain = 0x7F;
    slots[slot_index].state = 2;
    audio_update_guard[zero] = 0;
}
