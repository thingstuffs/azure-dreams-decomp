#include "common.h"

typedef struct {
    u8 pad0[0x8c];
    void *next;
    u8 pad90[6];
    s16 delay;
    u8 pad98[3];
    u8 state;
} StateObj;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[4];
    s32 dx;
    s32 dy;
    s32 unk14;
} Motion;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xe];
    u8 x;
    u8 y;
} Params;

typedef struct {
    u8 pad0[0x1c];
    s32 flags;
    u8 pad20[8];
    u8 byte28;
    u8 pad29[0x41];
    u16 key6a;
} Entity;

typedef struct {
    u8 pad0[0xa];
    u16 count;
    u8 padc[4];
    s32 value;
} Global83460;

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern Global83460 D_80083460;
extern s32 D_800814A0[];
extern u8 D_800B2A60[];

extern void func_8009A028(Entity *, Global83460 *);
extern void func_800A2B04(Motion *, u8, u8);
extern void func_800AD4D0(Entity *);

void func_800B2CA0(StateObj *arg0, Motion *arg1, Params *arg2, Entity *arg3) {
    s32 state;
    s16 new_delay;
    s32 temp_dx;
    s32 temp_dy;
    s32 rounded_dx;
    s32 rounded_dy;

    state = arg0->state;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    func_800AD4D0(arg3);
    arg1->dx = (-*(s16 *)(D_8006CCD8 + ((arg3->key6a >> 8) & 0xe))) << 0xf;
    arg1->dy = (-*(s16 *)(D_8006CCE8 + ((arg3->key6a >> 8) & 0xe))) << 0xf;
    arg0->state++;
    if (arg2->flags & 0x8000) {
        if (arg3->byte28 == 0) {
            goto reset_one;
        }
        arg0->state = 2;
        goto done;
    }
    new_delay = -1;
    if (arg3->flags & 0x228) {
        new_delay = 8;
    }
    arg0->delay = new_delay;
    goto state_one;

state_one:
    temp_dx = arg1->dx;
    rounded_dx = temp_dx;
    if (temp_dx < 0) {
        rounded_dx = temp_dx + 3;
    }
    temp_dy = arg1->dy;
    arg1->dx = temp_dx - (rounded_dx >> 2);
    rounded_dy = temp_dy;
    if (temp_dy < 0) {
        rounded_dy = temp_dy + 3;
    }
    arg1->dy = temp_dy - (rounded_dy >> 2);
    if (arg0->delay > 0) {
        u16 delay = arg0->delay;
        arg0->delay = delay - 1;
        goto after_delay;
    }
    if (arg2->flags & 0x6000) {
        arg0->delay = 0;
    }
after_delay:
    if (arg0->delay != 0) {
        goto done;
    }
    if (arg3->byte28 != 0) {
        goto set_delay;
    }

reset_one:
    {
        Global83460 *global = &D_80083460;
        arg1->unk14 = 0;
        arg1->dy = 0;
        arg1->dx = 0;
        if (global->value == (s32)((u8 *)arg3 - 0x20)) {
            global->value &= 0x7fffffff;
        }
        global->count++;
        func_8009A028(arg3, global);
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        goto done;
    }

set_delay:
    arg0->delay = 8;
    arg0->state++;
    goto done;

state_two:
    {
        s16 divisor = arg0->delay;
        if (divisor != 0) {
            s32 target_x = (s32)arg2->x << 6;
            s32 pos_x = arg1->x - 0x20;
            arg1->dx = ((target_x - pos_x) << 0xf) / divisor;
            {
                s32 pos_y = arg1->y - 0x20;
                s32 target_y = (s32)arg2->y << 6;
                arg1->dy = ((target_y - pos_y) << 0xf) / arg0->delay;
            }
        }
        {
            u16 delay = arg0->delay;
            delay -= 1;
            arg0->delay = delay;
            if ((delay << 0x10) > 0) {
                goto done;
            }
        }
    }

    arg1->unk14 = 0;
    arg1->dy = 0;
    arg1->dx = 0;
    func_800A2B04(arg1, arg2->x, arg2->y);
    {
        if (D_80083460.value == (s32)((u8 *)arg3 - 0x20)) {
            D_80083460.value &= 0x7fffffff;
        }
        arg0->next = D_800B2A60;
    }

done:
    return;
}
