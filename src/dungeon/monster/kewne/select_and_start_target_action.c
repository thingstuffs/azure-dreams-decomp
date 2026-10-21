#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80171F9C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171F9C_0;   /* held_arg2 in select_and_start_target_action */


extern s32 select_sprite_entry();
extern s32 prepare_directional_attack();
extern s32 get_actor_height_difference();
extern s32 place_actor_at_directional_neighbor();
extern s32 try_claim_dungeon_action_slot();
extern s32 check_entity_interaction_compatibility();
extern s32 apply_camera_offset_and_select_target();
extern u8 D_80175E50[];
extern u8 D_80175E70[];
extern u8 D_80175EA8[];

/* Select and start an actor action based on the target delta. */
s32 select_and_start_target_action(Rec_func_800A9E70_arg0 *action_state, s32 action_param, void *visual_data, ActorRecord *actor) {
    s32 target_delta;
    s16 action_mode;
    u16 pending_amount;
    u8 status;
    u16 stored_amount;

    status = *((u8 *)actor + 0x71);
    {
        s32 target;

        ((u8 *)actor)[113] = status & 0x7F;
        action_mode = 0;
        if (g_dungeon_status.flags & 0x2000) {
            return -1;
        }

        target = place_actor_at_directional_neighbor(actor, ((S_80171F9C_0 *)(visual_data))->unk_24, ((S_80171F9C_0 *)(visual_data))->unk_25,
            actor->facing);
        if ((check_entity_interaction_compatibility(actor, target) << 16) == 0) {
            return 0;
        }
        if (g_dungeon_status.flags & 0x2000) {
            return -1;
        }
        if (!(actor->action_flags & 0x8000) && (g_dungeon_status.flags & 8)) {
            return -1;
        }

        target_delta = 0 - get_actor_height_difference(target, actor);
        if ((u32)((target_delta - 0x20) & 0xFFFF) < 0x21U) {
            action_mode = 1;
        } else if ((u32)((target_delta + 0x10) & 0xFFFF) < 0x31U) {
            action_mode = 2;
        } else if ((u32)((target_delta + 0x40) & 0xFFFF) >= 0x31U) {
            return action_mode;
        } else {
            action_mode = 3;
        }

        if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
            return -1;
        }
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
            return -1;
        }

        {
            u8 new_action;
            s32 selected_mode = action_mode;
            action_state->unk_9B.as_s8 = 0;
            if (selected_mode == 1) {
                action_state->unk_8C = 0;
                ((S_80171F9C_0 *)(visual_data))->unk_2C = D_80175E50;
                new_action = 0x11;
                action_state->unk_98 |= 8;
                action_state->unk_9A.as_s8 = new_action;
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
            } else if (selected_mode == 2) {
                action_state->unk_8C = 0;
                ((S_80171F9C_0 *)(visual_data))->unk_2C = D_80175E70;
                new_action = 0x17;
                action_state->unk_98 |= 8;
                action_state->unk_9A.as_s8 = new_action;
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
            } else {
                action_state->unk_8C = 0;
                ((S_80171F9C_0 *)(visual_data))->unk_2C = D_80175EA8;
                action_state->unk_9A.as_s8 = 0x18;
                actor->unk_84 = 0x7C;
                actor->unk_85 = 0;
                actor->flags1C &= 0xFFFBFFFF;
            }

            {
                u8 *phase_page;
                phase_page = (u8 *)0x80080000;
                select_sprite_entry(((S_80171F9C_0 *)(visual_data)),
                    ((S_80171F9C_0 *)(visual_data))->unk_2C[((*(s16 *)(phase_page + 0x3228) + actor->facing + 0x100)
                    >> 9) & 7], 0);
            }
            actor->pending_turn_updates--;
            prepare_directional_attack(actor, ((S_80171F9C_0 *)(visual_data)), actor->facing, 1, 0);
            stored_amount = action_state->unk_90.at02_u16.v;
            pending_amount = action_state->unk_A0.at02_u16.v;
            action_state->unk_A0.at02_u16.v = 0;
            action_state->unk_9E.as_s16 = 0;
            action_state->unk_90.at02_u16.v = stored_amount - pending_amount;
            return action_mode;
        }
    }
}
