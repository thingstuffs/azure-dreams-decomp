#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/object_flags.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "town/person/object.h"

/* Clears the object slot and sets the object and global removal flags. */
void clear_object_slot_and_mark_removed(void *object) {
    s32 slot = ((TownObjectRecord *)object)->slot;

    object_index_slots[slot].object = 0;
    NODE_HEADER(object)->flags |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
