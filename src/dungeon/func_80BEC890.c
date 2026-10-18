#include "modules/dungeon_resource16_slot0.h"

void begin_eligible_actor_action(Rec_func_800A9E70_arg0 *action_state, s32 context, Rec_D_80082E80 *animation, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, context, 8, 0x300);
        if ((((s16)try_claim_dungeon_action_slot(actor)) << 0x10) == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            action_state->unk_9B.as_s8 = 0;
            animation->unk_2C.as_pu8 = ((u8 *)D_8017423C);
            func_80047784(animation, ((u8 *)D_8017423C)[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
            prepare_directional_attack(actor, animation, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}
