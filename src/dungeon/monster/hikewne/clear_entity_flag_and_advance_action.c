#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/effect.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */

/* Clear the entity flag and advance its action state when the checks pass. */
void clear_entity_flag_and_advance_action(ActorRecord *action_state, ObjectPosition *effect_context, SpriteFrameState *update_context, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, effect_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_8C.handler = 0;
            action_state->action_id.u = 0x11;
            action_state->action_phase.u = 0;
            action_state->action_timer.u = 0;
            entity->pending_turn_updates = (u8) (((u8)entity->pending_turn_updates) - 1);
            prepare_directional_attack(entity, update_context, entity->facing, 1, 0);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
