#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"






/* Initialize the object with resource 0x4A and set its state to 1. */
void init_reaction_object_slot_clut(TownObjectRecord *object, ObjectPosition *unused, struct SpriteFrameState *state) {
    register_object_slot_with_tables(object, 0x4A, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    state->clut = 1;
}
