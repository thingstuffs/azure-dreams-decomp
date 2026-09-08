#include "common.h"

typedef struct EffectState EffectState;
typedef struct EffectWork EffectWork;
typedef struct EffectColor EffectColor;

struct EffectState {
    s16 type;
    u16 count;
    s8 pad_04[0x0c];
    u16 phase;
    s16 max;
    s16 current;
    s16 angle;
    s16 mode;
    EffectWork *work;
};

struct EffectWork {
    s16 pad_00;
    s16 value;
    s16 pad_04;
    s16 height;
    s32 position;
    s8 pad_0c[8];
    s32 offset;
};

struct EffectColor {
    s8 pad_00[0x0c];
    u8 r;
    u8 g;
    u8 b;
    s8 pad_0f[0x0d];
    u16 value_1c;
    u16 value_1e;
};

extern s32 D_800814A0[3];
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);

/* Updates effect brightness, paired color values, and motion through three stages. */
void func_800C4640(EffectState *state, EffectWork *work, EffectColor *color) {
    s16 stage;

    stage = state->type;
    if (stage == 1) {
        goto type1;
    }
    if (stage < 2) {
        if (stage == 0) {
            goto type0;
        }
        goto common;
    }
    if (stage == 2) {
        goto type2;
    }
    goto common;

type0:
    {
        u8 old_brightness;
        s32 brightness;
        s32 old_pair_value;
        u16 pair_value;

        old_brightness = color->b;
        brightness = old_brightness + (((state->mode != 0 ? 0xf0 : 0x40) - old_brightness) / ((s16 *)state)[1]);
        old_pair_value = color->value_1e;
        color->b = brightness;
        color->g = brightness;
        color->r = brightness;
        pair_value = old_pair_value + (((state->mode != 0 ? 0x100 : 0x400) - old_pair_value) / ((s16 *)state)[1]);
        color->value_1e = pair_value;
        color->value_1c = pair_value;
        work->offset -= 0x200;
    }
    if (((state->count = state->count - 1) << 16) > 0) {
        goto common;
    }
    state->count = 8;
    state->type++;
    goto common;

type1:
    {
        u8 brightness;

        work->offset += 0x1800;
        if (state->mode != 0) {
            if (rand() & 3) {
                brightness = 0x10;
            } else {
                brightness = 0xf0;
            }
            color->b = brightness;
            color->g = brightness;
            color->r = brightness;
        }
    }
    if (((state->count = state->count - 1) << 16) > 0) {
        goto common;
    }
    state->count = 0x20;
    state->type++;
    goto common;

type2:
    {
        u8 brightness;
        s16 ticks_left;

        work->offset += 0x2000;
        if (state->mode != 0) {
            if (rand() & 3) {
                goto type2_value_constant;
            }
            ticks_left = state->count;
            brightness = ((ticks_left << 4) - ticks_left) >> 1;
            goto type2_value_done;
        type2_value_constant:
            brightness = 0x10;
        type2_value_done:
            color->b = brightness;
            color->g = brightness;
            color->r = brightness;
        }
    }
    if (((state->count = state->count - 1) << 16) <= 0) {
        u16 *flags;

        flags = ((u16 *)state) - 1;
        *flags |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

common:
    if (state->current < state->max) {
        s16 amplitude;

        amplitude = state->current + 2;
        state->current = amplitude;
        if (state->max < amplitude) {
            state->current = state->max;
        }
    }

    {
        u16 next_phase;
        u16 next_angle;

        next_phase = state->phase + 1;
        state->phase = next_phase;
        next_angle = state->angle + (func_800644B8((next_phase << 16) >> 8) >> 6);
        state->angle = next_angle;
        work->value = state->work->value + ((func_80064584((s16)next_angle) * state->current) >> 12);
    }

    {
        s32 height_product;

        height_product = func_800644B8((s16)state->angle) * state->current;
        work->height = state->work->height + (height_product >> 12);
        work->position += work->offset;
    }
}
