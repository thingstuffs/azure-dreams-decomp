#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 35 with its four data tables. */
void init_person_slot_thirty_five(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 35, D_800D57A4, D_800D57A8, D_800D5774, D_800D577C);
}
