#include "common.h"
#include "shared/object_node.h"
#include "shared/object_index_slots.h"
#include "town/player/object.h"
#include "town/player/record.h"

extern s32 *D_800D05E0[];

/* Initializes the object state and registers its enclosing record globally. */
void initialize_player_object(void *object_arg) {
    TownPlayerRecord *object = object_arg;

    u8 *global_state;

    object->handler_entries = D_800D05E0;
    object->slot = 1;
    global_state = object_index_slots;
    *(void **)(global_state + 0xC) = NODE_HEADER(object);
    global_state[8] = 0;
}
