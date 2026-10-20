#include "common.h"

typedef struct {
    short field_0;
    char pad4[6];
    unsigned short field_8;
    unsigned short field_A;
} S_8005B2C8_D80086C00;

extern S_8005B2C8_D80086C00 audio_sequence_slots[8];

/* Copies the indexed entry's two unsigned short fields to the output pointers. */
void copy_indexed_entry_pair(short index, int unused, unsigned short *out_field_8, unsigned short *out_field_a)
{
    S_8005B2C8_D80086C00 *base = audio_sequence_slots;
    S_8005B2C8_D80086C00 *entry = &base[index];
    *out_field_8 = entry->field_8;
    *out_field_a = entry->field_A;
}
