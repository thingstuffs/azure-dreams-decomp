#include "common.h"
#include "engine/audio/sequence.h"

extern SoundSequenceSlot audio_sequence_slots[8];

/* Stores two 7-bit values in the selected entry, then calls audio_refresh_sequence_voice_volumes for it. */
void set_sound_slot_byte_pair(s16 index, s32 value_8, s32 value_a)
{
    SoundSequenceSlot *entries = audio_sequence_slots;
    SoundSequenceSlot *entry = entries + index;
    entry->left_gain = value_8 & 0x7F;
    entry->right_gain = value_a & 0x7F;
    audio_refresh_sequence_voice_volumes();
}
