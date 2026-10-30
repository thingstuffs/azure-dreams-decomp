#include "shared/entity.h"
#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/noise/update_timed_actor_movement_and_scale.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/item.h"

/* Updates timed actor movement and sprite scaling, then handles completion. */
void update_timed_actor_movement_and_scale(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s16 direction_scratch;
    s32 current_state;

    switch (state->action_phase.u) {
    case 0:
    {
        u16 next_count;

        next_count = state->unk_9E.u - 1;
        state->unk_9E.s = next_count;
        if ((next_count << 16) > 0)
            break;
        sprite->frameTable = D_80174EA8;
        select_sprite_entry(sprite,
                      D_80174EA8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        state->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        state->unk_9E.s = 5;
        state->unk_A4.value = 0;
        state->action_phase.u += 1;
    }
                    /* fall through */
    case 1:
    {
        s16 frames_left;
        s32 target_x;
        s32 current_x;
        s32 current_y;
        s16 scale_frame;
        u16 next_count;

        state->unk_90.value -= state->unk_A4.value;
        frames_left = state->unk_9E.s;
        if (frames_left != 0) {
            target_x = sprite->tile_x << 6;
            current_x = motion->x.w.i - 0x20;
            motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            current_y = motion->y.w.i - 0x20;
            motion->velocity_y = (((sprite->tile_y << 6) - current_y) << 16) /
                               state->unk_9E.s;
            frames_left = state->unk_9E.s;
            state->unk_A4.value = (-rsin(frames_left * 0x199)) << 9;
        }

        state->unk_90.value += state->unk_A4.value;
        scale_frame = state->unk_9E.s;
        switch (scale_frame) {
        case 5:
            sprite->scale_x = 0xc00;
            sprite->scale_y = 0x1400;
            break;
        case 4:
            sprite->scale_x = 0xa00;
            sprite->scale_y = 0x1600;
            break;
        case 3:
            sprite->scale_x = 0xe00;
            sprite->scale_y = 0x1200;
            break;
        case 2:
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            break;
        }
        next_count = state->unk_9E.u - 1;
        state->unk_9E.s = next_count;
        if ((next_count << 16) < 0) {
            state->unk_90.value = 0;
            state->action_state_flags &= 0xfff7;
            actor->flags1C |= ACTOR_GROUNDED;
            state->action_phase.u += 1;
        }
    }
                    /* fall through */
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            state->action_state_flags &= 0xfff7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->frameTable = D_80174EB0;
            select_sprite_entry(sprite,
                          D_80174EB0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                          0);
            state->action_phase.u += 1;
        }
        break;
    case 3:
        sprite->scale_x = 0x1000;
        sprite->scale_y = 0x1000;
        break;
    }

    {
        u16 next_timer;

        next_timer = state->action_timer.u - 1;
        state->action_timer.s = next_timer;
        if ((next_timer << 16) <= 0) {
            s32 actor_flags;

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            spend_actor_mp(actor, 4);
            advance_status_timers(actor);
            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0)
                g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
            actor_flags = actor->flags1C;
            if (actor_flags & 0x2000) {
                if (actor->action_flags & 0x8000) {
                    actor->action_flags &= 0x7fff;
                }
            } else {
                if (!(actor_flags & 0x410)) {
                    if (actor_flags & 0x20000) {
                        actor->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                                                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                                                        &direction_scratch);
                    }
                }
            }
            if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
                state->unk_8C.address = update_actor_behavior_and_direction;
                on_actor_status_updated(actor);
            }
        }
    }
}
