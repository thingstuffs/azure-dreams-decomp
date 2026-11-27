#include "common.h"
#include "shared/object_node.h"
#include "shared/object_index_slots.h"
#include "town/player/object.h"
#include "town/player/record.h"

extern s32 *D_800D05E0[];

/* Initializes the object state and registers its enclosing record globally. */
void initialize_player_object(void *object_arg) {
    TownPlayerRecord *object = object_arg;

    ObjectIndexSlot *slots;

    object->handler_entries = D_800D05E0;
    object->slot = 1;
    slots = object_index_slots;
    slots[1].object = NODE_HEADER(object);
    slots[1].motion_id = 0;
}
