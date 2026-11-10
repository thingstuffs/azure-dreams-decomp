/* Refresh paired object components and their high flags. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_800B6EE8. */
#include "town/shop/object_component_refresh_g00626.h"
#include "shared/object_flags.h"
#include "town/shop.h"

/* Flags both referenced objects for removal in each of five paired entries from the owner table. */
void submit_five_paired_entry_values(S_800B4648_0 *owner) {
    s32 entry_value;
    s32 entry_offset;
    s32 entry_index;

    entry_index = 0;
    do {
        entry_offset = entry_index * 4;
        entry_value = *((S_800B4648_1 *)((entry_offset + owner->unk_5C)))->unk_18;
        entry_index += 1;
        flag_optional_object_for_removal(entry_value);
        flag_optional_object_for_removal(*((S_800B4648_1 *)((entry_offset + owner->unk_5C)))->unk_48);
    } while (entry_index < 5);
}

/* Updates two object components and sets the object and global high flags. */
void refresh_object_components_and_high_flag(StorageMenuNode *object)
{
    u16 object_flags;
    s32 global_flags;

    if (object != 0) {
        submit_five_paired_entry_values((S_800B4648_0 *)&object->menu);
        release_null_terminated_entries(object->menu.allocations);
        object_flags = object->header.flags | 0x8000;
        global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        object->header.flags = object_flags;
        object_flag_block.flags = global_flags;
    }
}
