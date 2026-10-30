/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/effect.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack();
s16 try_claim_dungeon_action_slot(ActorRecord *actor);

/* Initialize action state and directional animation when the entity status permits. */
void initialize_status_gated_action(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity) {
    entity->movement_queue_state = (s8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->action_id.u = 0x11;
            action_state->unk_8C.handler = 0;
            action_state->action_phase.u = 0;
            select_sprite_entry(animation, *(*(u8 **)&animation->frameTable + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
            prepare_directional_attack(entity, animation, entity->facing, 1, 0);
            action_state->action_state_flags = (u16) (action_state->action_state_flags | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
