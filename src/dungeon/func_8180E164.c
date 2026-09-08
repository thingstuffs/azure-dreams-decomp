#include "common.h"

typedef union {
    s16 s;
    u16 u;
    u8 b;
} S16U16;

typedef struct {
    u8 unk0[4];
    u16 flags;
    u8 unk6[4];
} DungeonState;

typedef struct {
    u8 unk0[4];
    void *link;
    u8 unk8[0x5c];
    s16 state;
    u16 count;
    u16 frame;
    S16U16 value;
} Effect;

typedef struct {
    u8 unk0[0xc];
    u8 color[3];
    u8 unk0f[0xb];
    u16 phase;
    s16 scale_y;
    s16 scale_x;
} Output;

typedef struct {
    Output *output;
} Link;

extern DungeonState D_80083160;
extern s32 D_800814A0[3];
extern s32 func_800644B8(s32);

/* Advance the effect fades, animate its scale and phase, and pulse the linked output brightness. */
void func_80027164(Effect *effect, void *unused, Output *output) {
    u16 tick;
    u16 brightness;
    u16 state;
    u16 duration;
    s16 scale;
    Output *linked_output;
    DungeonState *dungeon = &D_80083160;

    if (effect->state == 0) {
        tick = effect->count - 1;
        effect->count = tick;
        if ((tick << 0x10) <= 0) {
            duration = 0x38;
            effect->count = duration;
            state = effect->state;
            goto increment_state;
        }
        goto update;
    }

    if (effect->state == 1) {
        if (dungeon->flags & 1) {
            brightness = (u16)((s32)(effect->value.u << 0x10) >> 0x11);
        } else {
            if (effect->value.s < 0xc0) {
                effect->value.u = effect->value.u + 8;
            }
            brightness = effect->value.b;
        }
        output->color[2] = (u8)brightness;
        output->color[1] = (u8)brightness;
        output->color[0] = (u8)brightness;
        tick = effect->count - 1;
        effect->count = tick;
        if ((tick << 0x10) <= 0) {
            duration = 0x1c;
            effect->count = duration;
            state = effect->state;
            goto increment_state;
        }
        goto update;
    }

    goto state_other;

increment_state:
    effect->state = state + 1;
    goto update;

state_other:
    if (dungeon->flags & 1) {
        *(u32 *)&output->color[0] = 0;
    } else {
        if (effect->value.s > 0) {
            effect->value.u = effect->value.u - 8;
        }
        brightness = effect->value.b;
        output->color[2] = (u8)brightness;
        output->color[1] = (u8)brightness;
        output->color[0] = (u8)brightness;
    }
    tick = effect->count - 1;
    effect->count = tick;
    if ((tick << 0x10) <= 0) {
        ((u16 *)effect)[-1] = ((u16 *)effect)[-1] | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

update:
    tick = effect->frame + 1;
    effect->frame = tick;
    if (effect->state != 0) {
        scale = (func_800644B8((s32)(tick << 0x10) >> 7) >> 4) + 0x1000;
        output->scale_y = scale;
        output->scale_x = scale;
        output->phase = output->phase + 0x555;
        linked_output = ((Link *)((u8 *)effect->link - 0x14))->output;
        linked_output->color[0] = (u8)(((*(volatile u16 *)&effect->frame & 3) << 4) + 0x40);
        linked_output->color[1] = (u8)(((*(volatile u16 *)&effect->frame & 3) << 4) + 0x40);
        linked_output->color[2] = (u8)(((*(volatile u16 *)&effect->frame & 3) << 4) + 0x40);
    }
}
