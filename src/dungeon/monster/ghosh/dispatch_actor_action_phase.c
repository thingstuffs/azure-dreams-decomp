#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"



#include "dungeon/player/object/action_state.h"
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Dispatches the actor's action state and updates its activity flags. */
s32 dispatch_actor_action_phase(Rec_func_800A9E70_arg0 *actor, s32 x, s32 y, s32 force_action)
{
    void *base = actor;
    s16 action_state;
    s32 result;

    if (((ActorRecord *)base)->unk_AC.halves.high.u != 0) {
        action_state = relink_entity_and_clear_high_flag(x, y, base, 3, 6,
                              (u8 *)base + 0x9C);
        if ((s16)action_state < 0) {
            return 0;
        }
        if ((force_action << 16) != 0) {
            advance_actor_path(base, x, y, base);
            return 0;
        }
    } else {
        action_state = 0;
    }

    switch (action_state) {
    case 0:
        result = 0xE;
        actor->unk_9A.as_s8 = result;
        update_actor_status_and_mp(base);
        return 0;

    case 2:
        advance_actor_path(actor, x, y, base);
        return 0;

    case 1:
        ((ActorRecord *)base)->movement_queue_state &= 0x7F;
        if ((has_pending_dungeon_activity(base) << 16) != 0) {
            result = 0;
            ((ActorRecord *)base)->action_flags &= 0x7FFF;
            return result;
        }
                        /* fall through */

    default:
        ((ActorRecord *)base)->movement_queue_state &= 0x7F;
        result = 1;
        if (!(g_dungeon_status.flags & 8)) {
            return result;
        }
        result = 0;
        ((ActorRecord *)base)->action_flags &= 0x7FFF;
        return result;
    }
}
