#include "common.h"

#include "common.h"
#include "engine/menu.h"
#include "slus/data.h"

/* Set 17 objects' data pointers using table-selected groups and 12-byte entries. */
void initialize_seventeen_object_pointers(s32 *objects, s32 *group_bases)
{
    s32 object_index;
    u32 entry_index;
    u32 group_index;
    s32 index_table;

    object_index = 0;
    index_table = (s32)menu_object_pointer_order;
    do {
        entry_index = *(u8 *)(object_index + index_table);
        group_index = entry_index / 21;

        *(s32 *)(objects[object_index] + 8) = group_bases[(u8)group_index] + ((u8)(entry_index
            - (group_index * 21)) * 12);
        object_index++;
    } while (object_index < 17);
}
