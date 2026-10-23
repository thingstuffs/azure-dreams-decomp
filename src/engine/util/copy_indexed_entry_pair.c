#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"

extern SoundSequenceSlot audio_sequence_slots[8];

/* Copies the indexed entry's two unsigned short fields to the output pointers. */
void copy_indexed_entry_pair(short index, int unused, unsigned short *out_field_8, unsigned short *out_field_a)
{
    SoundSequenceSlot *base = audio_sequence_slots;
    SoundSequenceSlot *entry = &base[index];
    *out_field_8 = entry->left_gain;
    *out_field_a = entry->right_gain;
}
