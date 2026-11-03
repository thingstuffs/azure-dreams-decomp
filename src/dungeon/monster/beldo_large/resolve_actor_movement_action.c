#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"


#include "dungeon/player/object/action_state.h"
#include "dungeon/monster/beldo_large.h"
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Update the actor's action delay, dispatch movement, and clear completed action flags. */
s32 resolve_actor_movement_action(ActorRecord *entity, ObjectPosition *action_ctx, SpriteFrameState *position, s32 force_move)
{
    ActorRecord *actor = entity;
    s16 action_result;
    s32 result;
    u8 delay;

    delay = actor->unk_AC.bytes[2];
    action_result = 0;
    if (delay == 0) {
        action_result = relink_entity_and_clear_high_flag(action_ctx, position, actor, 3, 6,
                                      (s32)&actor->unk_9C);
        if ((s16)action_result < 0) {
            return 0;
        }
        if ((force_move << 16) != 0) {
            advance_actor_movement_step(actor, action_ctx, position, actor);
            return 0;
        }
    } else {
        actor->unk_AC.bytes[2] = delay - 1;
    }

    switch (action_result) {
    case 0:
        result = 0xE;
        entity->action_id.s = result;
        update_actor_status_and_mp(actor);
        return 0;
    case 2:
        advance_actor_movement_step(entity, action_ctx, position, actor);
        return 0;
    case 1:
        actor->movement_queue_state &= 0x7F;
        if ((has_pending_dungeon_activity(actor) << 16) != 0) {
            result = 0;
            actor->action_flags &= 0x7FFF;
            return result;
        }
        break;
    }
    actor->movement_queue_state &= 0x7F;
    result = 1;
    if (!(g_dungeon_status.flags & 8)) {
        return result;
    }
    result = 0;
    actor->action_flags &= 0x7FFF;
    return result;
}
