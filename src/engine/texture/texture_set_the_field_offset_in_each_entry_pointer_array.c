#include "common.h"
#include "shared/item_menu.h"
#include "engine/texture.h"



/*
 * Writes the supplied word to offset 8 in each of count records addressed by the entry pointer
 * array.
 */
void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(ItemMenuPart **entries, DisplayPositionWords *value, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        entries[index]->vector = value;
    }
}
