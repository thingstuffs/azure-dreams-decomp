#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

s32 advance_status_timers();                      /* extern */


/* Reset the entity state, clear the target flag, and decrement its counter. */
void complete_actor_facing_action(Rec_func_800A9E70_arg0 *entity, s32 unused_1, s32 unused_2, EntityRec *target) {
    target->unk_71 = (u8) (target->unk_71 & 0x7F);
    entity->unk_8C = 0;
    entity->unk_9A.as_s8 = 0x17;
    entity->unk_9B.as_s8 = 0;
    advance_status_timers(target);
    target->unk_6D = (u8) (((u8)target->unk_6D) - 1);
}
