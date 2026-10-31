#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/monster/hikewne.h"

#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/state.h"

void update_actor_status_and_mp();                      /* extern */


/* Update entity state and flags according to the state query result. */
s32 update_entity_state_from_query(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = body;

    state_type = (s16)relink_entity_and_clear_high_flag(position, sprite, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        select_movement_direction_and_advance(entity, position, sprite, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((ActorRecord *)entity)->action_id.s = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        select_movement_direction_and_advance(entity, position, sprite, entity);
        result = 0;
        return result;
    case 1:
        ((ActorRecord *)entity)->movement_queue_state = (u8) (((ActorRecord *)entity)->movement_queue_state & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((ActorRecord *)entity)->movement_queue_state = (u8) (((ActorRecord *)entity)->movement_queue_state & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((ActorRecord *)entity)->action_flags = (u16) (((ActorRecord *)entity)->action_flags & 0x7FFF);
    return result;
}
