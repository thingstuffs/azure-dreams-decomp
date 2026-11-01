#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"


extern void clear_slots_of_type(void *, s32);
struct ActorRecord;
extern s16 try_claim_dungeon_action_slot(struct ActorRecord *actor);

/* Reset action state and decrement the actor counter when the checks pass. */
void reset_action_and_decrement_actor_count(ActorRecord *action_state, void *unused_1, void *unused_2, void *actor) {
    *((u8 *) actor + 0x71) &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && (try_claim_dungeon_action_slot(actor) << 0x10) == 0 &&
        (try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        if ((set_or_clear_actor_status_slot(actor, STATUS_NO_TILE_OCCUPANCY, 0) << 0x10) < 0) {
            *(u16 *) ((u8 *) actor + 0x46) &= 0x7FFF;
            return;
        }
        action_state->unk_8C.word = 0;
        action_state->action_id.u = 0x18;
        action_state->action_phase.u = 0;
        action_state->action_timer.s = 0;
        action_state->unk_B0.bytes[3] = 0;
        action_state->unk_B0.bytes[1] = 0;
        action_state->unk_B0.bytes[2] = 0;
        *(s32 *) ((u8 *) actor + 0x1C) &= 0xFFFBFFFF;
        action_state->action_state_flags |= 8;
        clear_slots_of_type(actor, STATUS_POISON);
        advance_status_timers(actor);
        *((u8 *) actor + 0x6D) -= 1;
    }
}
