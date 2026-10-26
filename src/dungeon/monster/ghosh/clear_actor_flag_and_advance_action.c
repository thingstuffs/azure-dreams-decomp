#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
typedef struct Ent Ent;

/* cfail-repair: tf7-phase1-cache-v3 */
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */


/* Clear the actor flag and update its action state when both checks pass. */
void clear_actor_flag_and_advance_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *effect_context, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_8C.handler = 0;
            action_state->action_id = 0x11;
            action_state->action_phase = 0;
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, effect_context, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 6;
        }
    }
}
