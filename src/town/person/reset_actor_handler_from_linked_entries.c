#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

#include "shared/object_index_slots.h"

/*
 * Initializes entries from linked data offset 0x18, clears the indexed object slot, and installs
 * the step callback with count 32.
 */
void reset_actor_handler_from_linked_entries(TownObjectRecord *actor, ObjectPosition *unused_position, SpriteFrameState *output) {
    s32 *entries = actor->descriptor->entries[6];

    initialize_object_entries(actor, output, entries);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = step_person_y_down;
    actor->timer = 32;
}
