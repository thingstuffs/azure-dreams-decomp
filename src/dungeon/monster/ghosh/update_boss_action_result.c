#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/monster/ghosh.h"



extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void update_actor_status_and_mp(ActorRecord *entity);
#include "dungeon/player/object/action_state.h"

/* Updates an entity's state and flags according to its action result. */
s32 update_boss_action_result(ActorRecord *body, s32 target_x, s32 target_y, s16 force_action) {
    void *entity_data = body;
    s16 action_result;

    if (((ActorRecord *)entity_data)->unk_B0.halves.low.u != 0) {
        action_result = relink_entity_and_clear_high_flag(target_x, target_y, entity_data, 3, 6, (u8 *)entity_data + 0x9C);
        if (action_result < 0) {
            return 0;
        }
        if (force_action != 0) {
            advance_boss_actor_movement_state(entity_data, target_x, target_y, entity_data);
            return 0;
        }
    } else {
        action_result = 0;
    }

    switch (action_result) {
    case 0:
        body->action_id.u = 14;
        update_actor_status_and_mp(entity_data);
        return 0;

    case 2:
        advance_boss_actor_movement_state(body, target_x, target_y, entity_data);
        return 0;

    case 1:
        ((ActorRecord *)entity_data)->movement_queue_state &= 0x7F;
        if ((s16)has_pending_dungeon_activity(entity_data) != 0) {
            ((ActorRecord *)entity_data)->action_flags &= 0x7FFF;
            return 0;
        }
                        /* fallthrough */
    default:
        ((ActorRecord *)entity_data)->movement_queue_state &= 0x7F;
        if (!(g_dungeon_status.flags & 8)) {
            return 1;
        }
        ((ActorRecord *)entity_data)->action_flags &= 0x7FFF;
        return 0;
    }
}
