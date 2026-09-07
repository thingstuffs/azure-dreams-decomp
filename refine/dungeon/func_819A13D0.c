#include "common.h"

typedef struct {
    u8 pad00[0x3A];
    u16 count;
    s16 divisor;
} Work;

typedef struct {
    u8 pad00[0x0C];
    s8 c0;
    s8 c1;
    s8 c2;
    u8 pad0F[0x0B];
    u16 angle;
} Obj;

extern s16 D_800261B0[];
extern s32 D_800814A0[];

/* Decrement the count, update the object angle and components, and flag completion. */
void func_819A13D0(Work *work, s32 unused, Obj *obj) {
    s32 scaled_count;
    u16 count;
    u16 angle;

    count = work->count - 1;
    scaled_count = (s32)((s32)(count << 16) >> 9) / work->divisor;
    work->count = count;
    angle = obj->angle;
    D_800261B0[0] = 1;
    obj->angle = angle + 0x190;
    obj->c2 = scaled_count;
    obj->c1 = scaled_count;
    obj->c0 = scaled_count;
    if ((s16)work->count > 0) {
        return;
    }
    *(u16 *)((u8 *)work - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
