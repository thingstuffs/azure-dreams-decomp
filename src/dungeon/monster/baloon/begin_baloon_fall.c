#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/effect.h"
#include "dungeon/monster/baloon.h"
#include "dungeon/player/object.h"

/* Reset motion and transfer the pending amount after the entity checks pass. */
void begin_baloon_fall(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *unused, ActorRecord *actor) {
    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(actor), motion, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            body->unk_8C.word = 0;
            body->action_id = 0x18;
            body->action_phase = 0;
            body->action_timer = 0;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            body->unk_90.parts.high = body->unk_90.parts.high + actor->ground_height;
            body->unk_B4.halves.low.u = actor->ground_height;
            actor->ground_height = 0U;
            body->action_state_flags = (u16) (body->action_state_flags | 8);
            advance_status_timers(actor);
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
        }
    }
}
