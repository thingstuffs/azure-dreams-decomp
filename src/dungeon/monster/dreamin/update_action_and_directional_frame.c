#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern void prepare_directional_attack();

#include "dungeon/monster/dreamin.h"
#include "engine/graphics.h"

/* Update actor action state and select its directional animation. */
void update_action_and_directional_frame(ActorRecord *action_state, ObjectPosition *update_arg, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state &= 0x7F;

    if (!(g_dungeon_status.flags & 0x2000) &&
        ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) &&
        (apply_camera_offset_and_select_target((u8 *)actor - 0x20, update_arg, 8, 0x300),
         ((try_claim_dungeon_action_slot(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x17;
            actor->unk_84 = 0x10;
            actor->unk_85 = 0x10;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
        (sprite->frameTable) = dreamin_direction_frames;
        select_sprite_entry(sprite,
                      dreamin_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->pending_turn_updates--;

        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 == 0x11) {
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        }
    }
}
