#include "common.h"

typedef struct {
    /* 0x0 */ u8 pad[8];
    /* 0x8 */ s32 unk8;
} UnkStruct491CC;

/*
 * Writes the supplied word to offset 8 in each of count records addressed by the entry pointer
 * array.
 */
void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(UnkStruct491CC **entries, s32 value, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        entries[index]->unk8 = value;
    }
}
