#include "town/person.h"
#include "shared/sprite_frame_state.h"

/* Register person slot 51 with its four data tables. */
void init_person_slot_fifty_one(TownObjectRecord *body, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    TownObjectRecord *object = body;

    register_object_slot_with_tables(object, 51, bunny_state_handlers, bunny_script_action_handlers, bunny_animation_lists, bunny_descriptor);
}
