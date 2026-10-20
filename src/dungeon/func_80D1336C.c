#include "dungeon/monster/noise/update_timed_actor_movement_and_scale.h"

/* Updates timed actor movement and sprite scaling, then handles completion. */
void update_timed_actor_movement_and_scale(T_80172B6C_State *state, T_80172B6C_Motion *motion, T_80172B6C_Sprite *sprite, T_80172B6C_Actor *actor) {
    s16 direction_scratch;
    s32 current_state;

    switch (state->state_9b) {
    case 0:
    {
        u16 next_count;

        next_count = state->count_9e.u - 1;
        state->count_9e.u = next_count;
        if ((next_count << 16) > 0)
            break;
        sprite->ptr_2c = D_80174EA8;
        select_sprite_entry(sprite,
                      D_80174EA8[((g_game_work.view.viewAngle + actor->value_2a + 0x100) >> 9) & 7],
                      0);
        state->flags_98 |= 8;
        actor->flags_1c &= 0xf7ffffff;
        state->count_9e.u = 5;
        state->value_a4 = 0;
        state->state_9b += 1;
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

        state->value_90 -= state->value_a4;
        frames_left = state->count_9e.s;
        if (frames_left != 0) {
            target_x = sprite->value_24 << 6;
            current_x = motion->value_02 - 0x20;
            motion->value_0c = ((target_x - current_x) << 16) / frames_left;
            current_y = motion->value_06 - 0x20;
            motion->value_10 = (((sprite->value_25 << 6) - current_y) << 16) /
                               state->count_9e.s;
            frames_left = state->count_9e.s;
            state->value_a4 = (-func_800644B8(frames_left * 0x199)) << 9;
        }

        state->value_90 += state->value_a4;
        scale_frame = state->count_9e.s;
        switch (scale_frame) {
        case 5:
            sprite->value_1c = 0xc00;
            sprite->value_1e = 0x1400;
            break;
        case 4:
            sprite->value_1c = 0xa00;
            sprite->value_1e = 0x1600;
            break;
        case 3:
            sprite->value_1c = 0xe00;
            sprite->value_1e = 0x1200;
            break;
        case 2:
            sprite->value_1c = 0x1000;
            sprite->value_1e = 0x1000;
            break;
        }
        next_count = state->count_9e.u - 1;
        state->count_9e.u = next_count;
        if ((next_count << 16) < 0) {
            state->value_90 = 0;
            state->flags_98 &= 0xfff7;
            actor->flags_1c |= 0x08000000;
            state->state_9b += 1;
        }
    }
                    /* fall through */
    case 2:
        if (actor->flags_1c & 0x08000000) {
            state->flags_98 &= 0xfff7;
            motion->value_14 = 0;
            motion->value_10 = 0;
            motion->value_0c = 0;
            set_record_integer_tile_center(motion, sprite->value_24, sprite->value_25);
            sprite->value_1e = 0x1000;
            sprite->value_1c = 0x1000;
            sprite->ptr_2c = D_80174EB0;
            select_sprite_entry(sprite,
                          D_80174EB0[((g_game_work.view.viewAngle + actor->value_2a + 0x100) >> 9) & 7],
                          0);
            state->state_9b += 1;
        }
        break;
    case 3:
        sprite->value_1c = 0x1000;
        sprite->value_1e = 0x1000;
        break;
    }

    {
        u16 next_timer;

        next_timer = state->value_96 - 1;
        state->value_96 = next_timer;
        if ((next_timer << 16) <= 0) {
            s32 actor_flags;

            motion->value_14 = 0;
            motion->value_10 = 0;
            motion->value_0c = 0;
            set_record_integer_tile_center(motion, sprite->value_24, sprite->value_25);
            sprite->value_1c = 0x1000;
            sprite->value_1e = 0x1000;
            reduce_actor_food_meter(actor, 4);
            advance_status_timers(actor);
            if (g_dungeon_status.unk_08 != 0)
                g_dungeon_status.unk_08 = (u16)g_dungeon_status.unk_08 - 1;
            actor_flags = actor->flags_1c;
            if (actor_flags & 0x2000) {
                if (actor->flags_46 & 0x8000) {
                    actor->flags_46 &= 0x7fff;
                }
            } else {
                if (!(actor_flags & 0x410)) {
                    if (actor_flags & 0x20000) {
                        actor->value_2a = get_rounded_facing_and_rounding_flag(sprite->value_24, sprite->value_25,
                                                        D_80082E80.tileX, D_80082E80.tileY,
                                                        &direction_scratch);
                    }
                }
            }
            if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
                state->ptr_8c = update_actor_behavior_and_direction;
                on_actor_status_updated(actor);
            }
        }
    }
}
