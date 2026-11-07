#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/effect/shade.h"
#include "dungeon/player/object.h"
#include "engine/entity.h"

struct ActorRecord;

/* Reset action state and decrement the actor counter when the checks pass. */
void reset_action_and_decrement_actor_count(ActorRecord *action_state, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *actor) {
    actor->movement_queue_state &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && (try_claim_dungeon_action_slot(actor) << 0x10) == 0 &&
        (try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        if ((set_or_clear_actor_status_slot(actor, STATUS_NO_TILE_OCCUPANCY, 0) << 0x10) < 0) {
            actor->action_flags &= 0x7FFF;
            return;
        }
        action_state->unk_8C.word = 0;
        action_state->action_id = 0x18;
        action_state->action_phase = 0;
        action_state->action_timer.s = 0;
        action_state->unk_B0.bytes[3] = 0;
        action_state->unk_B0.bytes[1] = 0;
        action_state->unk_B0.bytes[2] = 0;
        actor->flags1C &= 0xFFFBFFFF;
        action_state->action_state_flags |= 8;
        clear_slots_of_type(actor, STATUS_POISON);
        advance_status_timers(actor);
        *((u8 *) actor + 0x6D) -= 1;
    }
}
