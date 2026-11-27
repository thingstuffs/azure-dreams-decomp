#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

extern u8 granny_animation_lists[];
extern u8 granny_descriptor[];
extern u8 granny_state_handlers[];
extern u8 granny_script_action_handlers[];

/* Configure the actor with type 0x30 and its data tables. */
void init_granny_person(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    register_object_slot_with_tables(actor, 0x30, granny_state_handlers, granny_script_action_handlers, granny_animation_lists, granny_descriptor);
}
