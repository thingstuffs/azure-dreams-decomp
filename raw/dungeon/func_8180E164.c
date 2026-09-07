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

void func_80027164(Effect *arg0, void *arg1, Output *arg2) {
    u16 count;
    u16 value;
    u16 next_state;
    u16 reset_count;
    s16 scale;
    Output *output;
    DungeonState *dungeon = &D_80083160;

    if (arg0->state == 0) {
        count = arg0->count - 1;
        arg0->count = count;
        if ((count << 0x10) <= 0) {
            reset_count = 0x38;
            arg0->count = reset_count;
            next_state = arg0->state;
            goto increment_state;
        }
        goto update;
    }

    if (arg0->state == 1) {
        if (dungeon->flags & 1) {
            value = (u16)((s32)(arg0->value.u << 0x10) >> 0x11);
        } else {
            if (arg0->value.s < 0xc0) {
                arg0->value.u = arg0->value.u + 8;
            }
            value = arg0->value.b;
        }
        arg2->color[2] = (u8)value;
        arg2->color[1] = (u8)value;
        arg2->color[0] = (u8)value;
        count = arg0->count - 1;
        arg0->count = count;
        if ((count << 0x10) <= 0) {
            reset_count = 0x1c;
            arg0->count = reset_count;
            next_state = arg0->state;
            goto increment_state;
        }
        goto update;
    }

    goto state_other;

increment_state:
    arg0->state = next_state + 1;
    goto update;

state_other:
    if (dungeon->flags & 1) {
        *(u32 *)&arg2->color[0] = 0;
    } else {
        if (arg0->value.s > 0) {
            arg0->value.u = arg0->value.u - 8;
        }
        value = arg0->value.b;
        arg2->color[2] = (u8)value;
        arg2->color[1] = (u8)value;
        arg2->color[0] = (u8)value;
    }
    count = arg0->count - 1;
    arg0->count = count;
    if ((count << 0x10) <= 0) {
        ((u16 *)arg0)[-1] = ((u16 *)arg0)[-1] | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

update:
    count = arg0->frame + 1;
    arg0->frame = count;
    if (arg0->state != 0) {
        scale = (func_800644B8((s32)(count << 0x10) >> 7) >> 4) + 0x1000;
        arg2->scale_y = scale;
        arg2->scale_x = scale;
        arg2->phase = arg2->phase + 0x555;
        output = ((Link *)((u8 *)arg0->link - 0x14))->output;
        output->color[0] = (u8)(((*(volatile u16 *)&arg0->frame & 3) << 4) + 0x40);
        output->color[1] = (u8)(((*(volatile u16 *)&arg0->frame & 3) << 4) + 0x40);
        output->color[2] = (u8)(((*(volatile u16 *)&arg0->frame & 3) << 4) + 0x40);
    }
}
