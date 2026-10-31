#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect.h"


   /* p2 in validate_action_and_apply_effect */


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
extern s32 probe_directional_neighbor(void *, u8, u8, s16); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
struct ActorRecord;
extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s16 check_entity_interaction_compatibility(void *, s32);

/* Validates an actor action, applies its effect, and updates the action state and remaining count. */
/* Starts Hikewne's attack against a compatible neighbor within 64 height units; returns 1, 0 if
 * unsuitable, or -1 if busy. */
s32 validate_action_and_apply_effect(ActorRecord *action, ObjectPosition *effect, SpriteFrameState *target, ActorRecord *actor_data) {
    void *actor = actor_data;
    s32 action_ready;
    s32 target_code;
    u8 actor_flags;

    actor_flags = (*((u8 *)actor + 0x71));
    {

        actor_flags = (u8)(actor_flags & 0x7F);
        ((ActorRecord *)actor)->movement_queue_state = actor_flags;
        action_ready = 0;

        if (g_dungeon_status.flags & 0x2000) {
            return -1;
        }

        target_code = probe_directional_neighbor(
            actor, target->tile_x, target->tile_y,
            ((ActorRecord *)actor)->facing);
        {
            s32 result = 0;

            if (check_entity_interaction_compatibility(actor, target_code) == 0) {
                return action_ready;
            }
            if (g_dungeon_status.flags & 0x2000) {
                return -1;
            }
            if ((((ActorRecord *)actor)->action_flags & 0x8000) == 0) {
                if (g_dungeon_status.flags & 8) {
                    return -1;
                }
            }

            if ((u16)(0 - get_actor_height_difference(target_code, actor) + 0x40) >= 0x81U) {
                return action_ready;
            }

            action_ready = 1;
            if ((((ActorRecord *)actor)->action_flags & 0x8000) == 0) {
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

            action->action_phase.u = 0;
            action->action_timer.u = 0;
            if (result != 0) {
                S_8017237C_3 *active_actor = actor;
                void *action_target = target;
                s32 facing;
                u8 remaining_count;

                action->unk_8C.run = 0;
                action->action_id.u = 0x11;
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
