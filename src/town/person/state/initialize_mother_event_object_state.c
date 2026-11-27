#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state.h"
#include "town/person/actor_output_state_g00671.h"

extern s32 D_800D6110[];

// Initializes the object with D_800D6110, clears its status, and sets state 0x62.
void initialize_mother_event_object_state(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite) {
    object->unk_A0 = 0;
    initialize_object_entries(object, sprite, D_800D6110);
    object_index_slots[object->slot].motion_id = 0;
    object->handler = raise_object_while_counter_runs;
    object->timer = 0x62;
}
