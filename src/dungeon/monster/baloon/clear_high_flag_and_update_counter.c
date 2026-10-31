#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */


/* Clears the object's high flag bit and conditionally resets state and decrements its counter. */
void clear_high_flag_and_update_counter(ActorRecord *body, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)
        && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        body->unk_8C.word = 0;
        body->action_id.s = 0x17;
        body->action_phase.s = 0;
        body->action_timer.s = 0;
        advance_status_timers(actor);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
    }
}
