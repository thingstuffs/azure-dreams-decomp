#include "modules/dungeon_resource17_slot0.h"

void func_801723A4(Rec_func_800A9E70_arg0 *action_state, void *context, Rec_D_80082E80 *animation,
    EntityRec *entity) {
    entity->unk_71 = (s8) (entity->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)entity - 0x20, context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            select_sprite_entry(animation, *(animation->unk_2C.as_pu8 + (((s32) (g_game_work.view.viewAngle + entity->facing
                + 0x100) >> 9) & 7)), 0);
            entity->unk_6D = (u8) (((u8)entity->unk_6D) - 1);
            prepare_directional_attack(entity, animation, entity->facing, 1, 0);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            entity->unk_84 = 0x7C;
            entity->unk_85 = 0;
        }
    }
}
