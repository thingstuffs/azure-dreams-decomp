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

void func_8002441C(void *arg0, s32 arg1, Arg81916C1C *arg2)
{
    Inner81916C1C *inner;
    State81916C1C *state;
    Prim81916C1C *prim;
    s32 index;
    s8 value;
    s8 count;

    inner = *(Inner81916C1C **)arg0;
    inner->counter++;
    state = D_80083160[0];
    prim = state->next;
    state->next = prim + 1;
    prim->x3 = 0x140;
    prim->x2 = 0;
    prim->y2 = 0;
    prim->y3 = 0xE0;
    index = arg2->count;
    prim->y0 = 0xC0;
    value = -0x40 - index * 0x30;
    prim->x1 = value;
    prim->x0 = value;
    func_800667A8(prim, index);
    prim->flags |= 2;
    func_8006658C((u8 *)D_80083160[0] + 0xB0, prim);
    count = (u8)arg2->count - 1;
    arg2->count = count;
    if ((count << 24) == 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Preserve the seed's exact 0x28 frame and s3/s2/s1/s0 held roles.
   A signed s32 index makes the s8 field emit one lb directly, removing the
   lbu plus sll/sra sign-extension residue and matching all 68 retail words. */
