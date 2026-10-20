#include "modules/dungeon_ovl_e0365c.h"

s32 begin_actor_directional_attack(void *action_state, void *action_ctx, void *sprite, EntityRec *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    s32 move_heading;
    u16 flags;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    move_heading = place_actor_at_directional_neighbor(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
        actor->facing);
    if ((check_entity_interaction_compatibility(actor, move_heading) << 0x10) == 0) {
        return 0;
    }
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - get_actor_height_difference(move_heading, actor)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_9A = 0x11;
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_9B = 0;
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        direction_table = &D_80174540;
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        select_sprite_entry(sprite, direction_table[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
