#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 19 with its four data tables. */
void init_person_slot_nineteen(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    TownObjectRecord *object = body;

    register_object_slot_with_tables(object, 19, barten_state_handlers, barten_script_action_handlers, barten_animation_lists, barten_descriptor);
}
