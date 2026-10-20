#include "modules/dungeon_ovl_cb9000.h"

s32 func_8016BFBC(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->unk_71;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = place_actor_at_directional_neighbor(actor, ((CL_CB9000_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_24,
                           ((CL_CB9000_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        ((CL_CB9000_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_2C = D_8016F2B4;
        select_sprite_entry(sprite_arg, D_8016F2B4[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D--;
        prepare_directional_attack(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
