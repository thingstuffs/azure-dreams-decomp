#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 try_claim_dungeon_action_slot();                          /* extern */
s32 advance_status_timers();                      /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */


typedef struct S_80174824_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80174824_1;   /* arg0 in reset_actor_action_state_after_completion */

/* Clears an entity flag and resets its action state after processing completes. */
void reset_actor_action_state_after_completion(S_80174824_1 *action_state, s32 context, s32 unused, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x17;
            action_state->unk_9B = 0;
            advance_status_timers(entity);
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
            action_state->unk_96 = 0;
        }
    }
}
