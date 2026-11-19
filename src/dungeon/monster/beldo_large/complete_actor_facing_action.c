#include "common.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/actor.h"



/* Reset the entity state, clear the target flag, and decrement its counter. */
void complete_actor_facing_action(ActorRecord *entity, ObjectPosition *unused_1, SpriteFrameState *unused_sprite, ActorRecord *target) {
    target->movement_queue_state = target->movement_queue_state & 0x7F;
    entity->unk_8C.handler = 0;
    entity->action_id = 0x17;
    entity->action_phase = 0;
    advance_status_timers(target);
    target->pending_turn_updates = target->pending_turn_updates - 1;
}
