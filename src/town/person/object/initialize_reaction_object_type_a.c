#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"






/* Initialize the object with resource 0x4A and set its state to 1. */
void initialize_reaction_object_type_4_a(void *object, void *unused, struct SpriteFrameState *state) {
    initialize_object_and_register_slot(object, 0x4A, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    state->clut = 1;
}
