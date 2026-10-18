#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

s32 try_claim_dungeon_action_slot();                          /* extern */
s32 advance_status_timers();                      /* extern */


/* Clears the object's high flag bit and conditionally resets state and decrements its counter. */
void clear_high_flag_and_update_counter(Rec_func_800A9E70_arg0 *state, s32 unused_1, s32 unused_2, EntityRec *object) {
    object->unk_71 = (u8) (object->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(object) << 0x10) == 0)
        && ((try_claim_dungeon_action_slot(object) << 0x10) == 0)) {
        state->unk_8C = 0;
        state->unk_9A.as_s8 = 0x17;
        state->unk_9B.as_s8 = 0;
        state->unk_96.as_s16 = 0;
        advance_status_timers(object);
        object->unk_6D = (u8) (((u8)object->unk_6D) - 1);
    }
}
