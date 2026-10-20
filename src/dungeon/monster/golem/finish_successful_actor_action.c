#include "common.h"

extern s32 update_actor_movement_to_tile(void *, s32, s32, s32);
extern void reduce_actor_food_meter(s32, s32);
extern void advance_status_timers(s32);
extern s32 check_actor_floor_trap(s32, s32);
extern s32 D_80170E94;

/* Update the actor after a successful action and reset the entity script on a positive result. */
void finish_successful_actor_action(void *action_entity, s32 action, s32 source_actor, s32 target_actor) {
    void *entity = action_entity;
    s32 source = source_actor;
    s32 actor = target_actor;

    if (update_actor_movement_to_tile(action_entity, action, source_actor, target_actor) != 0) {
        reduce_actor_food_meter(actor, 5);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(source, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E94;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
