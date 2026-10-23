/* Face target and start action.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00250 - CL:dungeon/func_80E0EC38@dungeon/bank_e2d000, CL:dungeon/func_80E0EC38@dungeon/bank_e33000, CL:dungeon/func_80E0EC38@dungeon/bank_e39000, CL:dungeon/func_80E0EC38@dungeon/bank_e3f000, CL:dungeon/func_80E0EC38@dungeon/bank_e45000, CL:dungeon/func_80E0EC38@dungeon/bank_e4b000, CL:dungeon/func_80E0EF2C@dungeon/bank_e2d000, CL:dungeon/func_80E0EF2C@dungeon/bank_e33000 (+4 more).
 */
#include "dungeon/monster/cyclone/face_target_and_start_action_g00250.h"
#include "dungeon/monster/cyclone.h"
#include "shared/actor_action_flags.h"

#include "shared/dungeon_status.h"
#include "shared/sprite_frame_state.h"/* Face the target and initialize the actor action when status checks allow it. */
void face_target_and_start_action(S_801722E4_3 *action_state, s32 event_context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 distance;
    void *actor_base;
    S_801722E4_2 *target;
    u8 *direction_frames;

    actor->movement_queue_state =
        (u8)(actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2008)) {
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            actor_base = (s8 *)actor - 0x20;
            apply_camera_offset_and_select_target(actor_base, event_context, 8, 0x300);
            if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
                target = ((S_801722E4_5_pre *)(actor->target))[-1].unk_00;
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->unk_24,
                    sprite->unk_25,
                    target->unk_24,
                    target->unk_25,
                    &distance);
                direction_frames = cyclone_frame_set_2;
                action_state->unk_9A = 0x17;
                action_state->unk_9B = 0;
                action_state->unk_8C = 0;
                sprite->frameTable = direction_frames;
                select_sprite_entry(
                    sprite,
                    direction_frames[((s32)(g_game_work.view.camera_rotation.parts.viewAngle +
                                    actor->facing + 0x100) >> 9) &
                             7],
                    0);
                advance_status_timers(actor);
                actor->pending_turn_updates =
                    (u8)(((u8)actor->pending_turn_updates) - 1);
                action_state->unk_98 =
                    (u16)(action_state->unk_98 | 8);
                select_nearby_target_and_initialize_slot(actor_base, event_context, 8, 0x300);
            }
        }
    }
}

/* Searches up to four tiles ahead for a target and starts the actor's action. */
s32 search_ahead_and_start_action(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 attempt;
    s32 tile_x;
    s32 tile_y;
    s32 direction;
    s32 step_offset;
    s32 next_x;
    s32 next_y;
    u16 call_direction;
    s16 *x_step;
    s16 *y_step;
    s16 floor_height;
    s32 target;

    actor->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    attempt = 0;
    direction = ((u16)((u16)actor->facing) >> 9) & 7;
    step_offset = direction << 1;
    tile_x = sprite->unk_24;
    tile_y = sprite->unk_25;
    x_step = (s16 *)((u8 *)((s8 *)dir_step_x) + step_offset);
    ((S_80172438_2 *)action_state)->unk_B2 = 0;
    call_direction = direction;

    do {
        s32 try_x = (s16)tile_x;
        s32 try_y = (s16)tile_y;
        s32 floor_x;
        s32 floor_y;

        ((S_80172438_2 *)action_state)->unk_B2++;
        if ((check_layer_offset_height((try_x << 6) & 0xFFC0,
                           (try_y << 6) & 0xFFC0,
                           actor->ground_height, call_direction << 9)
             << 16) != 0) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 2;
        }

        floor_y = (s16 *)((s8 *)dir_step_y);
        floor_x = (((try_x + *x_step) << 6) + 0x20) & 0xFFE0;
        y_step = (s16 *)(step_offset + (u8 *)floor_y);
        floor_y = (((try_y + *y_step) << 6) + 0x20) & 0xFFE0;
        floor_height = sample_terrain_surface_height(floor_x,
                              floor_y,
                              (s16)(((u16)actor->ground_height) - 0x20));
        if (floor_height >= 0x201) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }
        if ((u16)(floor_height - ((u16)actor->ground_height) + 0x3F) >= 0x7F) {
            ((S_80172438_2 *)action_state)->unk_B2--;
            return 3;
        }

        next_x = tile_x + *(u16 *)x_step;
        next_y = tile_y + *(u16 *)y_step;
        target = find_eligible_entry_at_coordinates(actor, (u16)next_x, (u16)next_y);
        actor->target = target;
        if (target != 0) {
            break;
        }

        attempt++;
        tile_x += *(u16 *)x_step;
        tile_y += *(u16 *)y_step;
    } while (attempt < 4);

    if (attempt >= 4) {
        return 3;
    }
    if ((check_entity_interaction_compatibility(actor, (void *)target) << 16) == 0) {
        return 0;
    }
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (g_dungeon_status.flags & 8)) {
        return -1;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    ((S_80172438_2 *)action_state)->unk_9B = 0;
    ((S_80172438_2 *)action_state)->unk_8C = 0;
    ((S_80172438_2 *)action_state)->unk_9A = 0x17;
    (sprite->frameTable) = cyclone_frame_set_2;
    select_sprite_entry(sprite,
                  cyclone_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                  0);
    advance_status_timers(actor);
    (*(u8 *)&actor->pending_turn_updates)--;
    return 1;
}

/* Update action state and select a direction-specific sprite when the actor is ready. */
void update_action_state_direction_specific(void *action_state, s32 action_param, SpriteFrameState *sprite, void *actor) {
    u8 *frame_table;
    s32 direction;

    *((u8 *)actor + 0x71) = (u8)(*((u8 *)actor + 0x71) & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        {
            void *actor_base = (u8 *)actor - 0x20;
            apply_camera_offset_and_select_target(actor_base, action_param, 8, 0x300);
        }
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            *((s8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *((s8 *)action_state + 0x9B) = 0;
            frame_table = &dungeon_resource_buffer[D_801764A0_OFF];
            sprite->frameTable = frame_table;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7;
            select_sprite_entry(sprite, frame_table[direction], 0);
            advance_status_timers(actor);
            *((u8 *)actor + 0x6D) = (u8)(*((u8 *)actor + 0x6D) - 1);
            *(u16 *)((u8 *)action_state + 0x98) = (u16)(*(u16 *)((u8 *)action_state + 0x98) | 8);
        }
    }
}

/* Clear the actor flag and, when allowed, start a directional animation and update its action state. */
void clear_actor_action_flag_and_animate(S_8017283C_1 *action_state, s32 action_context, SpriteFrameState *animation, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x18;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            animation->frameTable = cyclone_frame_set_2;
            select_sprite_entry(animation, cyclone_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
        }
    }
}

/* Attempt an actor action and initialize its state and directional animation on success. */
void attempt_actor_directional_action(S_8017294C_1 *action_state, s32 action_ctx, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x19;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            sprite->frameTable = cyclone_frame_set_2;
            select_sprite_entry(sprite, cyclone_frame_set_2[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
        }
    }
}
