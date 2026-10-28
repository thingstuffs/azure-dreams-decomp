#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 50 with its four data tables. */
void init_person_slot_fifty(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 50, D_800D71F4, D_800D71F8, D_800D71C4, D_800D71CC);
}
