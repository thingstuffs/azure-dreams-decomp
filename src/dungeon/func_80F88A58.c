#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

s32 has_pending_dungeon_activity();
void update_actor_status_and_food();
s32 relink_entity_and_clear_high_flag();
/* Update entity state and flags according to the state query result. */
s32 complete_actor_jump_to_destination(EntityRec *actor, void *primary_context, void *secondary_context, s32 force_move) {
    s16 state_type;
    s32 result;
    EntityRec *entity = actor;   /* the copy is load-bearing: it changes the callee-save order */

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context, secondary_context, entity, 3, 6, entity->pad_9C);
    if (state_type < 0) return 0;
    if ((force_move << 0x10) != 0) {
        select_bank_actor_movement(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        entity->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        select_bank_actor_movement(entity, primary_context, secondary_context, entity);
        result = 0;
        return result;
    case 1:
        entity->unk_71 &= 0x7F;
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        entity->unk_71 &= 0x7F;
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    entity->unk_46 &= 0x7FFF;
    return result;
}

