#include "modules/dungeon_resource10_slot0.h"

void select_actor_target_and_advance_status(void *action_state, s32 effect_arg, void *anim_state, EntityRec *actor) {
    actor->unk_71 = actor->unk_71 & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect_arg, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(s32 * *)((u8 *)anim_state + 0x2C)) = ((s32 *)D_801759D8);
            select_sprite_entry(anim_state,
                          *((((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)((s32 *)D_801759D8)),
                          0);
            advance_status_timers(actor);
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
    }
}
