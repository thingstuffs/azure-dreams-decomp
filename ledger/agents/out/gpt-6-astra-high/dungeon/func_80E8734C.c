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

/* Updates a timed movement animation, recenters the entity on its tile, and handles completion. */
void func_8014EB4C(void *action_state, void *motion, void *sprite, void *entity)
{
    s32 animation_phase;
    s32 move_frames_remaining;
    s32 target_tile_x;
    s32 position_x;
    s32 vertical_offset;
    s32 arc_offset;
    s32 position_y;
    s32 next_move_frame;
    s32 action_frames_remaining;
    s32 entity_flags;
    s32 direction_result;
    u8 *global_state;
    u8 *target_tile_data;
    u8 *idle_animation_table;

    animation_phase = FIELD(action_state, u8, 0x9B);
    if (animation_phase == 1) {
        goto state_one;
    }
    if (animation_phase < 2) {
        if (animation_phase == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (animation_phase == 2) {
        goto state_two;
    }
    if (animation_phase == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
{
    u8 *phase_animation_table;

    if (!(FIELD(sprite, u16, 0x14) & 0x6000)) {
        goto decrement_timer;
    }
    phase_animation_table = D_80151574;
    FIELD(sprite, u8 *, 0x2C) = phase_animation_table;
    func_80047784(sprite,
        phase_animation_table[((D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(sprite, s16, 0x1E) = 0x1000;
    FIELD(action_state, u16, 0x98) |= 8;
    FIELD(entity, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(action_state, s16, 0x9E) = 5;
    FIELD(action_state, s32, 0xA4) = 0;
    FIELD(action_state, u8, 0x9B)++;
}

state_one:
    move_frames_remaining = FIELD(action_state, s16, 0x9E);
    FIELD(action_state, s32, 0x90) -= FIELD(action_state, s32, 0xA4);
    if (move_frames_remaining != 0) {
        target_tile_x = FIELD(sprite, u8, 0x24);
        position_x = FIELD(motion, s16, 2);
        target_tile_x <<= 6;
        position_x -= 0x20;
        FIELD(motion, s32, 0xC) = ((target_tile_x - position_x) << 16) / move_frames_remaining;

        position_y = FIELD(motion, s16, 6);
        position_y -= 0x20;
        FIELD(motion, s32, 0x10) =
            (((FIELD(sprite, u8, 0x25) << 6) - position_y) << 16) /
            FIELD(action_state, s16, 0x9E);

        FIELD(action_state, s32, 0xA4) =
            (-func_800644B8(FIELD(action_state, s16, 0x9E) * 0x199)) << 10;
    }

    vertical_offset = FIELD(action_state, s32, 0x90);
    arc_offset = FIELD(action_state, s32, 0xA4);
    next_move_frame = FIELD(action_state, u16, 0x9E);
    vertical_offset += arc_offset;
    next_move_frame -= 1;
    FIELD(action_state, u16, 0x9E) = next_move_frame;
    FIELD(action_state, s32, 0x90) = vertical_offset;
    if ((next_move_frame << 16) >= 0) {
        goto state_two;
    }

    FIELD(action_state, s32, 0x90) = 0;
    FIELD(action_state, u16, 0x98) &= 0xFFF7;
    FIELD(entity, s32, 0x1C) |= 0x08000000;
    FIELD(action_state, u8, 0x9B)++;

state_two:
{
    u8 *phase_animation_table;

    if (FIELD(entity, s32, 0x1C) & 0x08000000) {
        FIELD(action_state, u16, 0x98) &= 0xFFF7;
        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0xC) = 0;
        func_800A2B04(motion, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
        phase_animation_table = D_8015157C;
        FIELD(sprite, u8 *, 0x2C) = phase_animation_table;
        func_80047784(sprite,
            phase_animation_table[((D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(sprite, s16, 0x1E) = 0xC00;
        FIELD(action_state, u8, 0x9B)++;
        goto decrement_timer;
    }
    goto decrement_timer;
}

state_three:
    idle_animation_table = D_80151554;
    if (FIELD(sprite, u8 *, 0x2C) != idle_animation_table) {
        FIELD(sprite, u8 *, 0x2C) = idle_animation_table;
        func_80047784(sprite,
            idle_animation_table[((D_80083228 + FIELD(entity, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(sprite, s16, 0x1E) = 0x1000;
    }

decrement_timer:
    action_frames_remaining = FIELD(action_state, u16, 0x96) - 1;
    FIELD(action_state, u16, 0x96) = action_frames_remaining;
    if ((action_frames_remaining << 16) > 0) {
        return;
    }

    FIELD(motion, s32, 0x14) = 0;
    FIELD(motion, s32, 0x10) = 0;
    FIELD(motion, s32, 0xC) = 0;
    FIELD(sprite, s16, 0x1E) = 0x1000;
    func_800A2B04(motion, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
    func_800AD594(entity, 3);
    func_800A4ACC(entity);

    global_state = (u8 *)&D_80083460;
    if (FIELD(global_state, s16, 8) != 0) {
        FIELD(global_state, u16, 8)--;
    }

    entity_flags = FIELD(entity, s32, 0x1C);
    if (entity_flags & 0x2000) {
        if (FIELD(entity, u16, 0x46) & 0x8000) {
            FIELD(entity, u16, 0x46) &= 0x7FFF;
        }
        goto collision_check;
    }
    if (entity_flags & 0x410) {
        goto collision_check;
    }
    if (!(entity_flags & 0x20000)) {
        goto collision_check;
    }
    target_tile_data = D_80082E80;
    FIELD(entity, s16, 0x2A) = func_800A0818(
        FIELD(sprite, u8, 0x24),
        FIELD(sprite, u8, 0x25),
        FIELD(target_tile_data, u8, 0x24),
        FIELD(target_tile_data, u8, 0x25),
        &direction_result);

collision_check:
    if ((func_800AD9B4(sprite, entity) << 16) > 0) {
        FIELD(action_state, void *, 0x8C) = D_8014D6F4;
        func_800A9A04(entity);
    }
}
