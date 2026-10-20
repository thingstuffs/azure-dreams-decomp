#include "engine/menu/entry_words.h"

#include "common.h"

/* Retail bytes at assets/54240.bin + 0x140; current ownership reconstruction only. */
s32 primitive_pair_secondary_color = 0x0098B8B8;
s32 primitive_pair_primary_color = 0x00586868;

#include "engine/menu/entry_words.h"

void *fill_primitive_pair(S_800508F0 *entry, u8 *template)
{
    entry->field4 = primitive_pair_primary_color;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];

    entry = entry + 1;
    entry->field4 = primitive_pair_secondary_color;
    entry->field1 = 0x48;
    entry->field2 = template[0];
    entry->field3 = template[2];
    entry->fieldA = template[4];
    entry->fieldB = template[6];
    entry->field0 = 3;

    return entry + 1;
}
