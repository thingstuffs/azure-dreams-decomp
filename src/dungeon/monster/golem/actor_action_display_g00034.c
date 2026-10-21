/* Actor action display (G00034).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00034 - CL:dungeon/func_81084A18@dungeon/bank_10a3000, CL:dungeon/func_81084A18@dungeon/bank_10a9000, CL:dungeon/func_81084A18@dungeon/bank_10af000, CL:dungeon/func_81084A18@dungeon/bank_10b5000, CL:dungeon/func_81084A18@dungeon/bank_10bb000, CL:dungeon/func_81084A18@dungeon/bank_10c1000.
 */
#include "dungeon/monster/golem/actor_action_display_g00034.h"

/* Attempts an actor action and initializes its output and directional display on success. */
s32 attempt_actor_action_and_display(void *action_out, s32 action_param, void *actor_info, void *acting_actor)
{
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    s32 computed_angle;
    s32 result;
    s32 action_code;
    u16 state_flags;

    ((S_80172050_0 *)acting_actor)->unk_71 &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        result = -1;
        return result;
    }

    computed_angle = place_actor_at_directional_neighbor(acting_actor, ((S_80172050_1 *)actor_info)->unk_24,
        ((S_80172050_1 *)actor_info)->unk_25, ((S_80172050_0 *)acting_actor)->unk_2A);
    if ((check_entity_interaction_compatibility(((void *)(acting_actor)), computed_angle) << 16) == 0) {
        result = 0;
        return result;
    }

    state_flags = g_dungeon_status.flags;
    if (state_flags & 0x2000) {
        result = -1;
        return result;
    }
    if (!(((S_80172050_0 *)acting_actor)->unk_46 & 0x8000)) {
        if (state_flags & 8) {
            result = -1;
            return result;
        }
    }

    if ((u16)(-get_actor_height_difference(computed_angle, acting_actor) + 0x3F) >= 0x7F) {
        result = 0;
        return result;
    }
    if ((try_claim_dungeon_action_slot((s32)acting_actor) << 16) != 0) {
        result = -1;
        return result;
    }

    apply_camera_offset_and_select_target((s32)((u8 *)acting_actor - 0x20), (void *)action_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot((s32)acting_actor) << 16) != 0) {
        result = -1;
    } else {
        ((S_80172050_2 *)action_out)->unk_9A = 0x11;
        action_code = 0x7C;
        ((S_80172050_2 *)action_out)->unk_9B = 0;
        ((S_80172050_2 *)action_out)->unk_8C = 0;
        ((S_80172050_0 *)acting_actor)->unk_84 = action_code;
        ((S_80172050_0 *)acting_actor)->unk_85 = 4;
        direction_table = &D_80175F48;
        (*(void * *)((u8 *)actor_info + 0x2C)) = direction_table;
        select_sprite_entry(actor_info,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172050_0 *)acting_actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172050_3 *)acting_actor)->unk_6D--;
        prepare_directional_attack(acting_actor, actor_info, ((S_80172050_3 *)acting_actor)->unk_2A, 1, 0);
        result = 1;
    }
    return result;
}

/* Update actor action state and directional animation when eligible. */
void update_eligible_actor_action(void *action_state, s32 action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot((s32)actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((s32)((u8 *)actor - 0x20), (void *)action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot((s32)actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_80175F48;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80175F48), 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 4;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            prepare_directional_attack((Ent *)actor, (Pos *)sprite, actor->facing, 1, 0);
        }
    }
}
