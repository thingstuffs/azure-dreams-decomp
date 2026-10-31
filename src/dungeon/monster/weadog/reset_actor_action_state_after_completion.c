#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
#include "dungeon/effect.h"

s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */

/* Clears an entity flag and resets its action state after processing completes. */
void reset_actor_action_state_after_completion(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *unused, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C.word = 0;
            action_state->action_id.s = 0x17;
            action_state->action_phase.s = 0;
            advance_status_timers(entity);
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
            action_state->action_timer.s = 0;
        }
    }
}
