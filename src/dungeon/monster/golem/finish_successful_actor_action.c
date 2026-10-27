#include "common.h"
#include "dungeon/monster/golem.h"
#include "dungeon/actor.h"

extern s32 update_actor_movement_to_tile(void *, s32, s32, s32);
extern void spend_actor_mp(s32, s32);
extern void advance_status_timers(s32);

/* Update the actor after a successful action and reset the entity script on a positive result. */
void finish_successful_actor_action(void *action_entity, s32 action, s32 source_actor, s32 target_actor) {
    ActorRecord *entity = action_entity;
    s32 source = source_actor;
    s32 actor = target_actor;

    if (update_actor_movement_to_tile(action_entity, action, source_actor, target_actor) != 0) {
        spend_actor_mp(actor, 5);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(source, actor) << 16) > 0) {
            entity->unk_8C.address = update_dungeon_actor_actions;
            entity->unk_90.value = 0;
        }
    }
}
