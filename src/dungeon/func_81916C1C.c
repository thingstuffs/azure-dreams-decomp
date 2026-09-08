#include "common.h"

typedef struct Prim81916C1C {
    u8 pad0[4];
    s8 x0;
    s8 x1;
    u8 y0;
    u8 flags;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
} Prim81916C1C;

typedef struct State81916C1C {
    u8 pad0[0x8D0];
    Prim81916C1C *next;
} State81916C1C;

typedef struct Inner81916C1C {
    u8 pad0[0x14];
    u16 counter;
} Inner81916C1C;

typedef struct Arg81916C1C {
    u8 pad0[5];
    s8 count;
} Arg81916C1C;

extern State81916C1C *D_80083160[3];
extern s32 D_800814A0;
extern void func_800667A8(Prim81916C1C *, s32);
extern void func_8006658C(void *, Prim81916C1C *);

/* Queue a full-screen primitive and mark completion when the countdown expires. */
void func_8002441C(void *context, s32 unused, Arg81916C1C *countdown)
{
    Inner81916C1C *tick_state;
    State81916C1C *render_state;
    Prim81916C1C *prim;
    s32 step;
    s8 x_value;
    s8 remaining;

    tick_state = *(Inner81916C1C **)context;
    tick_state->counter++;
    render_state = D_80083160[0];
    prim = render_state->next;
    render_state->next = prim + 1;
    prim->x3 = 0x140;
    prim->x2 = 0;
    prim->y2 = 0;
    prim->y3 = 0xE0;
    step = countdown->count;
    prim->y0 = 0xC0;
    x_value = -0x40 - step * 0x30;
    prim->x1 = x_value;
    prim->x0 = x_value;
    func_800667A8(prim, step);
    prim->flags |= 2;
    func_8006658C((u8 *)D_80083160[0] + 0xB0, prim);
    remaining = (u8)countdown->count - 1;
    countdown->count = remaining;
    if ((remaining << 24) == 0) {
        *(u16 *)((u8 *)context - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
