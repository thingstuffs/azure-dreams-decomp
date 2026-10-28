#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 19 with its four data tables. */
void init_person_slot_nineteen(void *body, void *unused_position, struct SpriteFrameState *unused_sprite) {
    PersonObject *object = body;

    initialize_object_and_register_slot(object, 19, D_800D5478, D_800D547C, D_800D5448, D_800D5450);
}
