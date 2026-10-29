#include "engine/graphics.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
extern u8 naplass_frame_set_4[8];


/* Start the actor's directional animation and update its action state when allowed. */
void start_naplass_status_action(ActorRecord *action_state, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        action_state->action_id.u = 0xD;
        action_state->unk_8C.handler = 0;
        action_state->action_phase.u = 0;
        sprite->frameTable = &naplass_frame_set_4;
        select_sprite_entry(sprite, naplass_frame_set_4[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)], 0);
        actor->flags1C = (s32) (actor->flags1C | ACTOR_ASLEEP);
        set_or_clear_actor_status_slot(actor, STATUS_SLEEP, 4);
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        advance_status_timers(actor);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}
