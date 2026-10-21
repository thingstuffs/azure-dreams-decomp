#include "common.h"
#include "engine/audio/sequence.h"

typedef struct {
    s16 field_0;
    char pad4[6];
    u16 field_8;
    u16 field_A;
} S_80086C00;

extern S_80086C00 audio_sequence_slots[8];

/* Stores two 7-bit values in the selected entry, then calls audio_refresh_sequence_voice_volumes for it. */
void set_sound_slot_byte_pair(s16 index, s32 value_8, s32 value_a)
{
    S_80086C00 *entries = audio_sequence_slots;
    S_80086C00 *entry = entries + index;
    entry->field_8 = value_8 & 0x7F;
    entry->field_A = value_a & 0x7F;
    audio_refresh_sequence_voice_volumes();
}
