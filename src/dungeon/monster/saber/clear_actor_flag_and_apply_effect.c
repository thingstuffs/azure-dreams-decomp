#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "engine/graphics.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern s32 saber_frame_set_1;

/* Clear the actor flag and apply an effect and animation change when allowed. */
void clear_actor_flag_and_apply_effect(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *anim_state, ActorRecord *actor) {
    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect_arg, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->action_id.s = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            action_state->action_phase.s = 0;
            (anim_state->frameTable) = &saber_frame_set_1;
            select_sprite_entry(anim_state,
                          *((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)&saber_frame_set_1),
                          0);
            advance_status_timers(actor);
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
    }
}
