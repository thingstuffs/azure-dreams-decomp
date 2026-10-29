#include "common.h"

#include "town/player/action_initializers.h"
#include "town/player.h"
extern void initialize_actor_movement_interaction_action(void *,void *,void *);
extern s32 town_actor_control[];

/* Dispatch the actor's action using its cached entry or the entry lookup result. */
void dispatch_actor_action(void *actor, void *position, void *context) {
    s32 cached_entry;
    s32 action_result;

    cached_entry = *(s32 *)((u8 *)actor + 0x2C);
    if (cached_entry != 0) {
        town_actor_control[4] = cached_entry;
        town_actor_control[6] = 0;
        initialize_actor_movement_interaction_action(actor, position, context);
    } else {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, position, context);
            } else {
                initialize_scene_action_record(actor, position, context);
            }
        } else {
            initialize_scene_action_record(actor, position, context);
        }
    }
}
