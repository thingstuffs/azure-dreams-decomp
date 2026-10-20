#include "modules/dungeon_resource06_slot0.h"
#include "shared/sprite_frame_state.h"

void update_actor_action_and_direction(void *action_state, void *context, SpriteFrameState *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((R06_80172428_S_80172428_1 *)action_state)->unk_9B = 0;
            sprite->frameTable = ((u8 *)D_8017587C);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)D_8017587C)), 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            ((R06_80172428_S_80172428_1 *)action_state)->unk_98 = (u16) (((R06_80172428_S_80172428_1 *)action_state)->unk_98 | 8);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}
