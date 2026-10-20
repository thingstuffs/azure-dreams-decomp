#include "dungeon/monster/noise/start_directional_action_and_record_tile.h"

/* Start the actor's directional action and record the adjacent tile result. */
void start_directional_action_and_record_tile(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    s32 direction;

    actor->unk_71 = (u8)(actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_96.as_s16 = 0xF;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80174EC8;
            select_sprite_entry(
                sprite,
                *(&D_80174EC8 + (((s32)(g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                0);
            ((Rec_func_800AA258_arg2 *)sprite)->unk_14 = (u16)(((Rec_func_800AA258_arg2 *)sprite)->unk_14 | 0x800);
            advance_status_timers(actor);
            actor->unk_6D = (u8)(((u8)actor->unk_6D) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target = find_eligible_actor_at_tile_and_height(
                actor,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_24 + ((u16 *)dir_step_x)[direction]) & 0xFFFF,
                (((Rec_func_800AA258_arg2 *)sprite)->unk_25 + ((u16 *)dir_step_y)[direction]) & 0xFFFF,
                actor->unk_88);
        }
    }
}
