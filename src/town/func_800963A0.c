#include "common.h"

extern void initialize_scene_action_record(void *, s32, s32);
extern void initialize_actor_movement_interaction_action(void *, s32, s32);
extern s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *, s32 *);
extern s32 D_800CFCB4[];

/* Dispatch the actor's action using its cached entry or the entry lookup result. */
void dispatch_actor_action(void *actor, s32 position, s32 context) {
    s32 cached_entry;
    s32 action_result;

    cached_entry = *(s32 *)((u8 *)actor + 0x2C);
    if (cached_entry != 0) {
        D_800CFCB4[4] = cached_entry;
        D_800CFCB4[6] = 0;
        initialize_actor_movement_interaction_action(actor, position, context);
    } else {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, D_800CFCB4);
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
