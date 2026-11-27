/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"
#include "town/person/object.h"

extern u8 weedy_animation_lists[];
extern u8 weedy_descriptor[];
extern u8 weedy_state_handlers[];
extern u8 weedy_script_action_handlers[];


/* Calls func_800C3050 with actor, 0x5, D_800D732C, D_800D7338, D_800D72FC, D_800D7304. */
void configure_actor_slot_5(TownObjectRecord *actor, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    register_object_slot_with_tables(actor, 0x5, weedy_state_handlers, weedy_script_action_handlers, weedy_animation_lists, weedy_descriptor);
}
