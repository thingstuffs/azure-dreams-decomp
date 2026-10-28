#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 33 with its four data tables. */
void init_person_slot_thirty_three(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 33, D_800D6C7C, D_800D6C80, D_800D6C4C, D_800D6C54);
}
