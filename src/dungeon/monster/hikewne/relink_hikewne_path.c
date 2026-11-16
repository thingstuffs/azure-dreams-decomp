#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/monster/hikewne.h"

#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/state.h"
#include "shared/actor_action_flags.h"



/* Update entity state and flags according to the state query result. */
s32 relink_hikewne_path(ActorRecord *actor, ObjectPosition *primary_context, SpriteFrameState *secondary_context, s32 force_move) {
    s16 state_type;
    s32 result;
    ActorRecord *entity = actor;   /* the copy is load-bearing: it changes the callee-save order */

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context, secondary_context, entity, 3, 6, &entity->unk_9C);
    if (state_type < 0) return 0;
    if ((force_move << 0x10) != 0) {
        choose_hikewne_move(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        entity->action_id = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_hikewne_move(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    case 1:
        entity->movement_queue_state &= 0x7F;
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        entity->movement_queue_state &= 0x7F;
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    return result;
}
