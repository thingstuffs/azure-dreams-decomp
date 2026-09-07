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

void func_800C4640(EffectState *state, EffectWork *work, EffectColor *color) {
    s16 type;

    type = state->type;
    if (type == 1) {
        goto type1;
    }
    if (type < 2) {
        if (type == 0) {
            goto type0;
        }
        goto common;
    }
    if (type == 2) {
        goto type2;
    }
    goto common;

type0:
    {
        u8 old_value;
        s32 value;
        s32 old_value_1e;
        u16 value_1e;

        old_value = color->b;
        value = old_value + (((state->mode != 0 ? 0xf0 : 0x40) - old_value) / ((s16 *)state)[1]);
        old_value_1e = color->value_1e;
        color->b = value;
        color->g = value;
        color->r = value;
        value_1e = old_value_1e + (((state->mode != 0 ? 0x100 : 0x400) - old_value_1e) / ((s16 *)state)[1]);
        color->value_1e = value_1e;
        color->value_1c = value_1e;
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
        u8 value;

        work->offset += 0x1800;
        if (state->mode != 0) {
            if (rand() & 3) {
                value = 0x10;
            } else {
                value = 0xf0;
            }
            color->b = value;
            color->g = value;
            color->r = value;
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
        u8 value;
        s16 count;

        work->offset += 0x2000;
        if (state->mode != 0) {
            if (rand() & 3) {
                goto type2_value_constant;
            }
            count = state->count;
            value = ((count << 4) - count) >> 1;
            goto type2_value_done;
        type2_value_constant:
            value = 0x10;
        type2_value_done:
            color->b = value;
            color->g = value;
            color->r = value;
        }
    }
    if (((state->count = state->count - 1) << 16) <= 0) {
        u16 *previous;

        previous = ((u16 *)state) - 1;
        *previous |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

common:
    if (state->current < state->max) {
        s16 current;

        current = state->current + 2;
        state->current = current;
        if (state->max < current) {
            state->current = state->max;
        }
    }

    {
        u16 phase;
        u16 angle;

        phase = state->phase + 1;
        state->phase = phase;
        angle = state->angle + (func_800644B8((phase << 16) >> 8) >> 6);
        state->angle = angle;
        work->value = state->work->value + ((func_80064584((s16)angle) * state->current) >> 12);
    }

    {
        s32 temp;

        temp = func_800644B8((s16)state->angle) * state->current;
        work->height = state->work->height + (temp >> 12);
        work->position += work->offset;
    }
}
