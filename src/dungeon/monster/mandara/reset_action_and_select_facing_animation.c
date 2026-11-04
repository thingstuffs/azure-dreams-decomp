#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
typedef struct Ent Ent;


extern Ent *prepare_directional_attack();
#include "dungeon/monster/mandara.h"
#include "engine/graphics.h"
#include "dungeon/effect.h"

/* Reset actor action state and select a facing-dependent animation when status checks pass. */
void reset_action_and_select_facing_animation(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state &= 0x7F;

    if (!(g_dungeon_status.flags & 0x2000) &&
        ((try_claim_dungeon_action_slot(actor) << 16) == 0) &&
        (apply_camera_offset_and_select_target(NODE_HEADER(actor), action_context, 8, 0x300),
         ((try_claim_dungeon_action_slot(actor) << 16) == 0))) {
        action_state->unk_8C.word = 0;
        action_state->action_phase.u = 0;

        if (action_state->action_state_flags & 0x8000) {
            action_state->action_id.u = 0x17;
            actor->unk_84 = 0x28;
            actor->unk_85 = 0x10;
        } else {
            action_state->action_id.u = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }

        (sprite->frameTable) = mandara_direction_frames;
        select_sprite_entry(
            sprite,
            mandara_direction_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    }
}
