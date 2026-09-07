#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8014D6F4[];
extern u8 D_80151554[];
extern u8 D_80151574[];
extern u8 D_8015157C[];

/* Advances a tile effect through its movement, animation, and collision states. */
void func_8014EB4C(void *effect_state, void *position, void *tile_context, void *collision_state)
{
    s32 effect_phase;
    s32 phase_ticks_remaining;
    s32 target_tile_x;
    s32 current_x;
    s32 position_accumulator;
    s32 velocity_step;
    s32 current_y;
    s32 phase_counter;
    s32 lifetime_timer;
    s32 collision_flags;
    s32 sampled_angle;
    u8 *global_state;
    u8 *map_origin;
    u8 *animation_table;

    effect_phase = FIELD(effect_state, u8, 0x9B);
    if (effect_phase == 1) {
        goto state_one;
    }
    if (effect_phase < 2) {
        if (effect_phase == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (effect_phase == 2) {
        goto state_two;
    }
    if (effect_phase == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
{
    u8 *direction_table;

    if (!(FIELD(tile_context, u16, 0x14) & 0x6000)) {
        goto decrement_timer;
    }
    direction_table = D_80151574;
    FIELD(tile_context, u8 *, 0x2C) = direction_table;
    func_80047784(tile_context,
        direction_table[((D_80083228 + FIELD(collision_state, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(tile_context, s16, 0x1E) = 0x1000;
    FIELD(effect_state, u16, 0x98) |= 8;
    FIELD(collision_state, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(effect_state, s16, 0x9E) = 5;
    FIELD(effect_state, s32, 0xA4) = 0;
    FIELD(effect_state, u8, 0x9B)++;
}

state_one:
    phase_ticks_remaining = FIELD(effect_state, s16, 0x9E);
    FIELD(effect_state, s32, 0x90) -= FIELD(effect_state, s32, 0xA4);
    if (phase_ticks_remaining != 0) {
        target_tile_x = FIELD(tile_context, u8, 0x24);
        current_x = FIELD(position, s16, 2);
        target_tile_x <<= 6;
        current_x -= 0x20;
        FIELD(position, s32, 0xC) = ((target_tile_x - current_x) << 16) / phase_ticks_remaining;

        current_y = FIELD(position, s16, 6);
        current_y -= 0x20;
        FIELD(position, s32, 0x10) =
            (((FIELD(tile_context, u8, 0x25) << 6) - current_y) << 16) /
            FIELD(effect_state, s16, 0x9E);

        FIELD(effect_state, s32, 0xA4) =
            (-func_800644B8(FIELD(effect_state, s16, 0x9E) * 0x199)) << 10;
    }

    position_accumulator = FIELD(effect_state, s32, 0x90);
    velocity_step = FIELD(effect_state, s32, 0xA4);
    phase_counter = FIELD(effect_state, u16, 0x9E);
    position_accumulator += velocity_step;
    phase_counter -= 1;
    FIELD(effect_state, u16, 0x9E) = phase_counter;
    FIELD(effect_state, s32, 0x90) = position_accumulator;
    if ((phase_counter << 16) >= 0) {
        goto state_two;
    }

    FIELD(effect_state, s32, 0x90) = 0;
    FIELD(effect_state, u16, 0x98) &= 0xFFF7;
    FIELD(collision_state, s32, 0x1C) |= 0x08000000;
    FIELD(effect_state, u8, 0x9B)++;

state_two:
{
    u8 *direction_table;

    if (FIELD(collision_state, s32, 0x1C) & 0x08000000) {
        FIELD(effect_state, u16, 0x98) &= 0xFFF7;
        FIELD(position, s32, 0x14) = 0;
        FIELD(position, s32, 0x10) = 0;
        FIELD(position, s32, 0xC) = 0;
        func_800A2B04(position, FIELD(tile_context, u8, 0x24), FIELD(tile_context, u8, 0x25));
        direction_table = D_8015157C;
        FIELD(tile_context, u8 *, 0x2C) = direction_table;
        func_80047784(tile_context,
            direction_table[((D_80083228 + FIELD(collision_state, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(tile_context, s16, 0x1E) = 0xC00;
        FIELD(effect_state, u8, 0x9B)++;
        goto decrement_timer;
    }
    goto decrement_timer;
}

state_three:
    animation_table = D_80151554;
    if (FIELD(tile_context, u8 *, 0x2C) != animation_table) {
        FIELD(tile_context, u8 *, 0x2C) = animation_table;
        func_80047784(tile_context,
            animation_table[((D_80083228 + FIELD(collision_state, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(tile_context, s16, 0x1E) = 0x1000;
    }

decrement_timer:
    lifetime_timer = FIELD(effect_state, u16, 0x96) - 1;
    FIELD(effect_state, u16, 0x96) = lifetime_timer;
    if ((lifetime_timer << 16) > 0) {
        return;
    }

    FIELD(position, s32, 0x14) = 0;
    FIELD(position, s32, 0x10) = 0;
    FIELD(position, s32, 0xC) = 0;
    FIELD(tile_context, s16, 0x1E) = 0x1000;
    func_800A2B04(position, FIELD(tile_context, u8, 0x24), FIELD(tile_context, u8, 0x25));
    func_800AD594(collision_state, 3);
    func_800A4ACC(collision_state);

    global_state = (u8 *)&D_80083460;
    if (FIELD(global_state, s16, 8) != 0) {
        FIELD(global_state, u16, 8)--;
    }

    collision_flags = FIELD(collision_state, s32, 0x1C);
    if (collision_flags & 0x2000) {
        if (FIELD(collision_state, u16, 0x46) & 0x8000) {
            FIELD(collision_state, u16, 0x46) &= 0x7FFF;
        }
        goto collision_check;
    }
    if (collision_flags & 0x410) {
        goto collision_check;
    }
    if (!(collision_flags & 0x20000)) {
        goto collision_check;
    }
    map_origin = D_80082E80;
    FIELD(collision_state, s16, 0x2A) = func_800A0818(
        FIELD(tile_context, u8, 0x24),
        FIELD(tile_context, u8, 0x25),
        FIELD(map_origin, u8, 0x24),
        FIELD(map_origin, u8, 0x25),
        &sampled_angle);

collision_check:
    if ((func_800AD9B4(tile_context, collision_state) << 16) > 0) {
        FIELD(effect_state, void *, 0x8C) = D_8014D6F4;
        func_800A9A04(collision_state);
    }
}
