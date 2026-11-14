#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/effect.h"
#include "dungeon/monster/death.h"
#include "dungeon/player/object.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */

/* Clears an actor flag, applies a conditional effect, and updates its action state. */
void begin_death_attack(ActorRecord *action_state, ObjectPosition *effect_context, SpriteFrameState *action_context, ActorRecord *actor) {
    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(actor), effect_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_8C.handler = 0;
            action_state->action_id = 0x11;
            action_state->action_phase = 0;
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
            prepare_directional_attack(actor, action_context, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 4;
        }
    }
}
