#include "common.h"
#include "shared/dungeon_status.h"

typedef struct S_8017237C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
} S_8017237C_0;   /* p3 in validate_action_and_apply_effect */

typedef struct S_8017237C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017237C_1;   /* p2 in validate_action_and_apply_effect */

typedef struct S_8017237C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
} S_8017237C_2;   /* p0 in validate_action_and_apply_effect */

typedef struct S_8017237C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x16];
    u8 unk_84;
    u8 unk_85;
} S_8017237C_3;   /* call0 in validate_action_and_apply_effect */


extern void prepare_directional_attack(void *, void *, s32, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 place_actor_at_directional_neighbor(void *, u8, u8, s16);
extern s16 try_claim_dungeon_action_slot(void *);
extern s16 check_entity_interaction_compatibility(void *, s32);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);

/* Validates an actor action, applies its effect, and updates the action state and remaining count. */
s32 validate_action_and_apply_effect(S_8017237C_2 *action, void *effect, S_8017237C_1 *target, void *actor_data)
{
    void *actor = actor_data;
    s32 action_ready;
    s32 target_code;
    u8 actor_flags;

    actor_flags = (*(u8 *)((u8 *)actor + 0x71));
    {

        actor_flags = (u8)(actor_flags & 0x7F);
        ((S_8017237C_0 *)actor)->unk_71 = actor_flags;
        action_ready = 0;

        if (g_dungeon_status.flags & 0x2000) {
            return -1;
        }

        target_code = place_actor_at_directional_neighbor(
            actor, target->unk_24, target->unk_25,
            ((S_8017237C_0 *)actor)->unk_2A);
        {
            s32 result = 0;

            if (check_entity_interaction_compatibility(actor, target_code) == 0) {
                return action_ready;
            }
            if (g_dungeon_status.flags & 0x2000) {
                return -1;
            }
            if ((((S_8017237C_0 *)actor)->unk_46 & 0x8000) == 0) {
                if (g_dungeon_status.flags & 8) {
                    return -1;
                }
            }

            if ((u16)(0 - get_actor_height_difference(target_code, actor) + 0x40) >= 0x81U) {
                return action_ready;
            }

            action_ready = 1;
            if ((((S_8017237C_0 *)actor)->unk_46 & 0x8000) == 0) {
                if (g_dungeon_status.flags & 8) {
                    return -1;
                }
            }
            if (try_claim_dungeon_action_slot(actor) != 0) {
                return -1;
            }

            apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect, 8, 0x300);

            if (try_claim_dungeon_action_slot(actor) != 0) {
                return -1;
            }
            result = action_ready;

            action->unk_9B = 0;
            action->unk_96 = 0;
            if (result != 0) {
                S_8017237C_3 *active_actor = actor;
                void *action_target = target;
                s32 facing;
                u8 remaining_count;

                action->unk_8C = 0;
                action->unk_9A = 0x11;
                facing = active_actor->unk_2A;
                active_actor->unk_84 = 0x7C;
                remaining_count = active_actor->unk_6D;
                active_actor->unk_85 = 0;
                active_actor->unk_6D = (u8)(remaining_count - 1);
                prepare_directional_attack(active_actor, action_target, facing, 1, 0);
            }

            return result;
        }
    }
}

/* MECHANISM: target_code is set once (the first call's result), so sched1's
   birthing boost launches its copy into $s1 right before the a1 use and the
   a0 move comes first; `result` (zero at its declaration, later action_ready)
   is the separate multi-set variable that keeps the tail copy `move $17,$18`. */
