#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/util.h"


/* Copies the indexed entry's two unsigned short fields to the output pointers. */
void get_sequence_slot_gains(short index, int unused, unsigned short *out_field_8, unsigned short *out_field_a)
{
    SoundSequenceSlot *base = audio_sequence_slots;
    SoundSequenceSlot *entry = &base[index];
    *out_field_8 = entry->left_gain;
    *out_field_a = entry->right_gain;
}
