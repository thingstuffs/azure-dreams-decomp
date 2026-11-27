#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "engine/graphics.h"
#include "dungeon/effect.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/player/object.h"

typedef struct Ent Ent;


Ent *prepare_directional_attack(); /* extern */
extern u8 cyclone_attack_start_direction_frames;

/*
 * Starts Cyclone's directional attack when an action slot is free, consumes a pending turn, and
 * prepares damage.
 */
void begin_cyclone_attack(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(actor), action_ctx, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->action_id = 0x11;
            action_state->unk_8C.word = 0;
            action_state->action_phase = 0;
            (sprite->frameTable) = &cyclone_attack_start_direction_frames;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &cyclone_attack_start_direction_frames), 0);
            actor->pending_turn_updates = actor->pending_turn_updates - 1;
            action_state->action_state_flags = (u16) (action_state->action_state_flags | 8);
            actor->accuracy = 0x7C;
            actor->attack_bonus = 0;
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        }
    }
}
