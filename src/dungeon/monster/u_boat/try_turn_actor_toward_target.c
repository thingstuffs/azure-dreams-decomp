#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"

void prepare_directional_attack(void *, void *, s16, s32, s32);
s32 get_actor_height_difference(s32, void *);
s32 probe_directional_neighbor(void *, u8, u8, s16);
s32 try_claim_dungeon_action_slot(void *);
s32 check_entity_interaction_compatibility(void *, s32);
void apply_camera_offset_and_select_target(void *,void *, s32, s32);
void begin_actor_exclusive_action(void *, ObjectPosition *, void *, s32, s32);
extern u8 resident_globals_page[];


/*
 * Checks a compatible neighbor within 64 height units, then starts U-Boat's normal attack or
 * exclusive action mode.
 */
s32 try_turn_actor_toward_target(Rec_func_800A9E70_arg0 *action_state, ObjectPosition *action_context, Rec_D_80082E80 *target, ActorRecord *actor) {
    s32 target_angle;
    u16 result;
    u16 *global_flags;

    result = actor->movement_queue_state & 0x7F;
    actor->movement_queue_state = result;
    {

        global_flags = (u16 *)(resident_globals_page + 0x3460);
    }
    result = 0;
    if (global_flags[1] & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, target->unk_24,
        target->unk_25, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 0x10) == 0) {
        return result;
    }

    if (global_flags[1] & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (global_flags[1] & 8)) {
        return -1;
    }
    if ((u32)(((0 - get_actor_height_difference(target_angle, actor)) + 0x40) & 0xFFFF) <
        0x81U) {
        result = 1;
        if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
            return -1;
        }
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
            return -1;
        }

        action_state->unk_9B.as_s8 = 0;
        if (action_state->unk_B5 == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
            action_state->unk_98 =
                (u16)(action_state->unk_98 | 8);
            prepare_directional_attack(actor, target, actor->facing, 1, 0);
            actor->pending_turn_updates--;
        } else {
            begin_actor_exclusive_action(action_state, action_context, target, 1, 1);
        }
    }
    return result;
}
