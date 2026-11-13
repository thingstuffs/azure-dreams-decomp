#include "common.h"
#include "shared/item_menu.h"
#include "engine/texture.h"



/*
 * Writes the supplied word to offset 8 in each of count records addressed by the entry pointer
 * array.
 */
void set_menu_part_vectors(ItemMenuPart **entries, DisplayPositionWords *value, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        entries[index]->vector = value;
    }
}
