/* actor slot global state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6674, PD:town/engine:800D667C, PD:town/engine:800D66A4, PD:town/engine:800D66A8. */
#include "town/person/actor_slot_global_state_g00680.h"
#include "town/scene/resource_request_data.h"
#include "shared/sprite_frame_state.h"
#include "town/person.h"

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 75 with the four local tables.
 */
void configure_actor_slot_75_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state) {
    actor->shared_animation = 1;
    state->animation_resource = loaded_town_resource_attributes[0];
    register_object_slot_with_tables(actor, 0x4B, horse_state_handlers, horse_script_action_handlers, horse_animation_lists,
                  horse_descriptor);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 76 with the four local tables.
 */
void configure_actor_slot_76_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state) {
    actor->shared_animation = 1;
    state->animation_resource = loaded_town_resource_attributes[0];
    register_object_slot_with_tables(actor, 0x4C, horse_state_handlers, horse_script_action_handlers, horse_animation_lists,
                  horse_descriptor);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 77 with the four local tables.
 */
void configure_actor_slot_77_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state) {
    actor->shared_animation = 1;
    state->animation_resource = loaded_town_resource_attributes[0];
    register_object_slot_with_tables(actor, 0x4D, horse_state_handlers, horse_script_action_handlers, horse_animation_lists,
                  horse_descriptor);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 78 with the four local tables.
 */
void configure_actor_slot_78_and_copy_global(TownObjectRecord *actor, ObjectPosition *unused, struct SpriteFrameState *state) {
    actor->shared_animation = 1;
    state->animation_resource = loaded_town_resource_attributes[0];
    register_object_slot_with_tables(actor, 0x4E, horse_state_handlers, horse_script_action_handlers, horse_animation_lists,
                  horse_descriptor);
}
