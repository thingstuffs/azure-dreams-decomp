#include "dungeon/monster/tyrant/check_action_eligibility_updates_actor_state_directional_animation_success.h"

/* Checks action eligibility and updates the actor state and directional animation on success. */
s32 check_action_eligibility_updates_actor_state_directional_animation_success(void *action_state, s32 action_id, void *sprite, EntityRec *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    s32 target_direction;
    u16 status_flags;
    u16 state_flag;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_direction = place_actor_at_directional_neighbor(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25, actor->facing);

    if ((((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)
        ? target_direction == 0
        : (check_entity_interaction_compatibility(actor, target_direction) << 0x10) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000)) {
        if (status_flags & 8) {
            return -1;
        }
    }

    if ((u32)(((0 - get_actor_height_difference(target_direction, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_id, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
    actor->unk_84 = 0x7C;
    actor->unk_85 = 0;
    state_flag = ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000;
    if (state_flag) {
        /* retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
        target_direction = 0;
    }
    (*(u8 **)((u8 *)sprite + 0x2C)) = D_80173FB8;
    select_sprite_entry(sprite,
        D_80173FB8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
    prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    return 1;
}
