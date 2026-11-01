#include "common.h"
#include "town/person.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

#include "shared/object_index_slots.h"

extern u8 D_800C3C7C[];


/*
 * Initializes entries from linked data offset 0x18, clears the indexed object slot, and installs
 * D_800C3C7C with count 32.
 */
void reset_actor_handler_from_linked_entries(TownObjectRecord *actor, s32 unused, SpriteFrameState *output) {
    s32 *entries = actor->descriptor->entries[6];

    initialize_object_entries(actor, output, entries);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = D_800C3C7C;
    actor->timer.as_s16 = 32;
}
