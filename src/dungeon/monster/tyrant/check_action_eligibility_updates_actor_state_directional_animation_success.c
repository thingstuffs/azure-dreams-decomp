#include "shared/sprite_frame_state.h"
#include "dungeon/monster/tyrant/check_action_eligibility_updates_actor_state_directional_animation_success.h"
#include "shared/actor_action_flags.h"

/* Checks action eligibility and updates the actor state and directional animation on success. */
s32 check_action_eligibility_updates_actor_state_directional_animation_success(void *action_state, void *action_id, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    s32 target_direction;
    u16 status_flags;
    u16 state_flag;

    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_direction = probe_directional_neighbor(actor, sprite->tile_x,
        sprite->tile_y, actor->facing);

    if ((((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)
        ? target_direction == 0
        : (check_entity_interaction_compatibility(actor, target_direction) << 0x10) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
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
    /* BYTES: retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
    if (state_flag) {
        target_direction = 0;
    }
    (sprite->frameTable) = tyrant_direction_frames;
    select_sprite_entry(sprite,
        tyrant_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
    prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
    return 1;
}
