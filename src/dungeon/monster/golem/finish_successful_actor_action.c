#include "common.h"
#include "dungeon/monster/golem.h"
#include "dungeon/actor.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

s32 update_actor_movement_to_tile(void *move_state, void *motion, void *target_tile, ActorRecord *actor);

/* Update the actor after a successful action and reset the entity script on a positive result. */
void finish_successful_actor_action(ActorRecord *action_entity, ObjectPosition *action, SpriteFrameState *source_actor, ActorRecord *target_actor) {
    ActorRecord *entity = action_entity;
    SpriteFrameState *source = source_actor;
    ActorRecord *actor = target_actor;

    if (update_actor_movement_to_tile(action_entity, action, source_actor, target_actor) != 0) {
        spend_actor_mp(actor, 5);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(source, actor) << 16) > 0) {
            entity->unk_8C.address = update_dungeon_actor_actions;
            entity->unk_90.value = 0;
        }
    }
}
