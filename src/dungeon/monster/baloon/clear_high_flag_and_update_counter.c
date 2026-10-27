#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/actor/status.h"

s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */


/* Clears the object's high flag bit and conditionally resets state and decrements its counter. */
void clear_high_flag_and_update_counter(Rec_func_800A9E70_arg0 *state, s32 unused_1, s32 unused_2, ActorRecord *object) {
    object->movement_queue_state = (u8) (object->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(object) << 0x10) == 0)
        && ((try_claim_dungeon_action_slot(object) << 0x10) == 0)) {
        state->unk_8C = 0;
        state->unk_9A.as_s8 = 0x17;
        state->unk_9B.as_s8 = 0;
        state->unk_96.as_s16 = 0;
        advance_status_timers(object);
        object->pending_turn_updates = (u8) (((u8)object->pending_turn_updates) - 1);
    }
}
