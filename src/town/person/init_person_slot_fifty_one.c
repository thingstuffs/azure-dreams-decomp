#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 51 with its four data tables. */
void init_person_slot_fifty_one(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 51, D_800D5270, D_800D5274, D_800D5240, D_800D5248);
}
