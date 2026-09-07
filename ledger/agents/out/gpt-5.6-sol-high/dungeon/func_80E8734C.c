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

// Advances an actor's scripted jump, landing animation, timeout, and collision response.
void func_8014EB4C(void *behavior, void *position, void *sprite, void *actor)
{
    s32 phase;
    s32 frames_remaining;
    s32 target_x;
    s32 current_x;
    s32 height_offset;
    s32 vertical_velocity;
    s32 current_y;
    s32 next_frame_count;
    s32 timeout;
    s32 actor_flags;
    s32 direction_data;
    u8 *dungeon_state;
    u8 *reference_sprite;
    u8 *animation_table;

    phase = FIELD(behavior, u8, 0x9B);
    if (phase == 1) {
        goto state_one;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (phase == 2) {
        goto state_two;
    }
    if (phase == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
{
    u8 *animation_table;

    if (!(FIELD(sprite, u16, 0x14) & 0x6000)) {
        goto decrement_timer;
    }
    animation_table = D_80151574;
    FIELD(sprite, u8 *, 0x2C) = animation_table;
    func_80047784(sprite,
        animation_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(sprite, s16, 0x1E) = 0x1000;
    FIELD(behavior, u16, 0x98) |= 8;
    FIELD(actor, s32, 0x1C) &= 0xF7FFFFFF;
    FIELD(behavior, s16, 0x9E) = 5;
    FIELD(behavior, s32, 0xA4) = 0;
    FIELD(behavior, u8, 0x9B)++;
}

state_one:
    frames_remaining = FIELD(behavior, s16, 0x9E);
    FIELD(behavior, s32, 0x90) -= FIELD(behavior, s32, 0xA4);
    if (frames_remaining != 0) {
        target_x = FIELD(sprite, u8, 0x24);
        current_x = FIELD(position, s16, 2);
        target_x <<= 6;
        current_x -= 0x20;
        FIELD(position, s32, 0xC) =
            ((target_x - current_x) << 16) / frames_remaining;

        current_y = FIELD(position, s16, 6);
        current_y -= 0x20;
        FIELD(position, s32, 0x10) =
            (((FIELD(sprite, u8, 0x25) << 6) - current_y) << 16) /
            FIELD(behavior, s16, 0x9E);

        FIELD(behavior, s32, 0xA4) =
            (-func_800644B8(FIELD(behavior, s16, 0x9E) * 0x199)) << 10;
    }

    height_offset = FIELD(behavior, s32, 0x90);
    vertical_velocity = FIELD(behavior, s32, 0xA4);
    next_frame_count = FIELD(behavior, u16, 0x9E);
    height_offset += vertical_velocity;
    next_frame_count -= 1;
    FIELD(behavior, u16, 0x9E) = next_frame_count;
    FIELD(behavior, s32, 0x90) = height_offset;
    if ((next_frame_count << 16) >= 0) {
        goto state_two;
    }

    FIELD(behavior, s32, 0x90) = 0;
    FIELD(behavior, u16, 0x98) &= 0xFFF7;
    FIELD(actor, s32, 0x1C) |= 0x08000000;
    FIELD(behavior, u8, 0x9B)++;

state_two:
{
    u8 *animation_table;

    if (FIELD(actor, s32, 0x1C) & 0x08000000) {
        FIELD(behavior, u16, 0x98) &= 0xFFF7;
        FIELD(position, s32, 0x14) = 0;
        FIELD(position, s32, 0x10) = 0;
        FIELD(position, s32, 0xC) = 0;
        func_800A2B04(position, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
        animation_table = D_8015157C;
        FIELD(sprite, u8 *, 0x2C) = animation_table;
        func_80047784(sprite,
            animation_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(sprite, s16, 0x1E) = 0xC00;
        FIELD(behavior, u8, 0x9B)++;
        goto decrement_timer;
    }
    goto decrement_timer;
}

state_three:
    animation_table = D_80151554;
    if (FIELD(sprite, u8 *, 0x2C) != animation_table) {
        FIELD(sprite, u8 *, 0x2C) = animation_table;
        func_80047784(sprite,
            animation_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(sprite, s16, 0x1E) = 0x1000;
    }

decrement_timer:
    timeout = FIELD(behavior, u16, 0x96) - 1;
    FIELD(behavior, u16, 0x96) = timeout;
    if ((timeout << 16) > 0) {
        return;
    }

    FIELD(position, s32, 0x14) = 0;
    FIELD(position, s32, 0x10) = 0;
    FIELD(position, s32, 0xC) = 0;
    FIELD(sprite, s16, 0x1E) = 0x1000;
    func_800A2B04(position, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
    func_800AD594(actor, 3);
    func_800A4ACC(actor);

    dungeon_state = (u8 *)&D_80083460;
    if (FIELD(dungeon_state, s16, 8) != 0) {
        FIELD(dungeon_state, u16, 8)--;
    }

    actor_flags = FIELD(actor, s32, 0x1C);
    if (actor_flags & 0x2000) {
        if (FIELD(actor, u16, 0x46) & 0x8000) {
            FIELD(actor, u16, 0x46) &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    reference_sprite = D_80082E80;
    FIELD(actor, s16, 0x2A) = func_800A0818(
        FIELD(sprite, u8, 0x24),
        FIELD(sprite, u8, 0x25),
        FIELD(reference_sprite, u8, 0x24),
        FIELD(reference_sprite, u8, 0x25),
        &direction_data);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        FIELD(behavior, void *, 0x8C) = D_8014D6F4;
        func_800A9A04(actor);
    }
}
