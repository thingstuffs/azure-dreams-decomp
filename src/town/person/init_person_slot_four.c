#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot four with its four data tables. */
void init_person_slot_four(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 4, D_800D60C0, D_800D60C4, D_800D6090, D_800D6098);
}
