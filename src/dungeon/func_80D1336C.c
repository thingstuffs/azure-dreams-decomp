#include "common.h"

typedef struct {
    u8 pad_00[0x8c];
    u8 *ptr_8c;
    s32 value_90;
    u8 pad_94[2];
    u16 value_96;
    u16 flags_98;
    u8 pad_9a;
    u8 state_9b;
    u8 pad_9c[2];
    union {
        u16 u;
        s16 s;
    } count_9e;
    u8 pad_a0[4];
    s32 value_a4;
} State;

typedef struct {
    u8 pad_00[2];
    s16 value_02;
    u8 pad_04[2];
    s16 value_06;
    u8 pad_08[4];
    s32 value_0c;
    s32 value_10;
    s32 value_14;
} Motion;

typedef struct {
    u8 pad_00[0x1c];
    s16 value_1c;
    s16 value_1e;
    u8 pad_20[4];
    u8 value_24;
    u8 value_25;
    u8 pad_26[6];
    u8 *ptr_2c;
} Sprite;

typedef struct {
    u8 pad_00[0x1c];
    s32 flags_1c;
    u8 pad_20[0xa];
    s16 value_2a;
    u8 pad_2c[0x1a];
    u16 flags_46;
} Actor;

extern s16 D_80083228[5];
extern s32 D_80083460[3];
extern u8 D_80082E80[];
extern u8 D_80171760[];
extern u8 D_80174EA8[];
extern u8 D_80174EB0[];

extern s32 func_800644B8(s32 value);
extern void func_80047784(Sprite *sprite, u8 value, s32 zero);
extern void func_800A2B04(Motion *motion, u8 x, u8 y);
extern void func_800AD594(Actor *actor, s32 value);
extern void func_800A4ACC(Actor *actor);
extern s16 func_800A0818(u8 x0, u8 y0, u8 x1, u8 y1, s16 *scratch);
extern s32 func_800AD9B4(Sprite *sprite, Actor *actor);
extern void func_800A9A04(Actor *actor);

/* Updates timed actor movement and sprite scaling, then handles completion. */
void func_80172B6C(State *state, Motion *motion, Sprite *sprite, Actor *actor) {
    s16 direction_scratch;
    s32 current_state;

    current_state = state->state_9b;
    if (current_state == 1)
        goto L_state_1;
    if (current_state < 2) {
        if (current_state == 0)
            goto L_state_0;
        goto L_update_96;
    } else {
        if (current_state == 2)
            goto L_flagged;
        if (current_state == 3)
            goto L_state_3;
        goto L_update_96;
    }

L_state_0: {
        u16 next_count;

        next_count = state->count_9e.u - 1;
        state->count_9e.u = next_count;
        if ((next_count << 16) > 0)
            goto L_update_96;
        sprite->ptr_2c = D_80174EA8;
        func_80047784(sprite,
                      D_80174EA8[((D_80083228[0] + actor->value_2a + 0x100) >> 9) & 7],
                      0);
        state->flags_98 |= 8;
        actor->flags_1c &= 0xf7ffffff;
        state->count_9e.u = 5;
        state->value_a4 = 0;
        state->state_9b += 1;
        goto L_state_1;
    }

L_state_1:
    {
        s16 frames_left;
        s32 target_x;
        s32 current_x;
        s32 current_y;

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
    }

L_after_motion:
    state->value_90 += state->value_a4;
    {
        s16 scale_frame;

        scale_frame = state->count_9e.s;
        if (scale_frame == 3)
            goto L_count_3;
        if (scale_frame < 4) {
            if (scale_frame == 2)
                goto L_count_2;
            goto L_decrement_count;
        }
        if (scale_frame == 4)
            goto L_count_4;
        if (scale_frame == 5)
            goto L_count_5;
        goto L_decrement_count;
    }

L_count_5:
    sprite->value_1c = 0xc00;
    sprite->value_1e = 0x1400;
    goto L_decrement_count;

L_count_4:
    sprite->value_1c = 0xa00;
    sprite->value_1e = 0x1600;
    goto L_decrement_count;

L_count_3:
    sprite->value_1c = 0xe00;
    sprite->value_1e = 0x1200;
    goto L_decrement_count;

L_count_2:
    sprite->value_1c = 0x1000;
    sprite->value_1e = 0x1000;

L_decrement_count: {
        u16 next_count;

        next_count = state->count_9e.u - 1;
        state->count_9e.u = next_count;
        if ((next_count << 16) < 0) {
            state->value_90 = 0;
            state->flags_98 &= 0xfff7;
            actor->flags_1c |= 0x08000000;
            state->state_9b += 1;
        }
    }

L_flagged:
    if (actor->flags_1c & 0x08000000) {
        state->flags_98 &= 0xfff7;
        motion->value_14 = 0;
        motion->value_10 = 0;
        motion->value_0c = 0;
        func_800A2B04(motion, sprite->value_24, sprite->value_25);
        sprite->value_1e = 0x1000;
        sprite->value_1c = 0x1000;
        sprite->ptr_2c = D_80174EB0;
        func_80047784(sprite,
                      D_80174EB0[((D_80083228[0] + actor->value_2a + 0x100) >> 9) & 7],
                      0);
        state->state_9b += 1;
        goto L_update_96;
    }
    goto L_update_96;

L_state_3:
    sprite->value_1c = 0x1000;
    sprite->value_1e = 0x1000;

L_update_96: {
        u16 next_timer;

        next_timer = state->value_96 - 1;
        state->value_96 = next_timer;
        if ((next_timer << 16) <= 0) {
            s16 *global_counts;
            s32 actor_flags;

            motion->value_14 = 0;
            motion->value_10 = 0;
            motion->value_0c = 0;
            func_800A2B04(motion, sprite->value_24, sprite->value_25);
            sprite->value_1c = 0x1000;
            sprite->value_1e = 0x1000;
            func_800AD594(actor, 4);
            func_800A4ACC(actor);
            global_counts = (s16 *)D_80083460;
            if (global_counts[4] != 0)
                global_counts[4] = (u16)global_counts[4] - 1;
            actor_flags = actor->flags_1c;
            if (actor_flags & 0x2000) {
                if (actor->flags_46 & 0x8000) {
                    actor->flags_46 &= 0x7fff;
                    goto L_after_flag;
                }
            } else {
                if (actor_flags & 0x410)
                    goto L_after_flag;
                if (!(actor_flags & 0x20000))
                    goto L_after_flag;
                actor->value_2a = func_800A0818(sprite->value_24, sprite->value_25,
                                                 D_80082E80[0x24], D_80082E80[0x25],
                                                 &direction_scratch);
            }
L_after_flag:
            if ((func_800AD9B4(sprite, actor) << 16) > 0) {
                state->ptr_8c = D_80171760;
                func_800A9A04(actor);
            }
        }
    }
}
