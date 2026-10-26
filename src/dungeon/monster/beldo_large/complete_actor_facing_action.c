#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

void advance_status_timers();                      /* extern */


/* Reset the entity state, clear the target flag, and decrement its counter. */
void complete_actor_facing_action(Rec_func_800A9E70_arg0 *entity, s32 unused_1, s32 unused_2, ActorRecord *target) {
    target->movement_queue_state = (u8) (target->movement_queue_state & 0x7F);
    entity->unk_8C = 0;
    entity->unk_9A.as_s8 = 0x17;
    entity->unk_9B.as_s8 = 0;
    advance_status_timers(target);
    target->pending_turn_updates = (u8) (((u8)target->pending_turn_updates) - 1);
}
