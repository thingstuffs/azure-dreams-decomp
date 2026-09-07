#include "common.h"

typedef union FixedWord {
    s32 value;
    struct {
        s16 lo;
        s16 hi;
    } part;
} FixedWord;

typedef struct MotionVector {
    FixedWord x;
    FixedWord y;
    FixedWord z;
} MotionVector;

typedef struct ObjectState {
    u8 pad00[0x18];
    u16 timer;
    s16 pad1A;
    s16 x;
    s16 y;
    s16 z;
    u8 pad22[0x3A];
    s32 dx;
    s32 dy;
    s32 dz;
    s32 ddx;
    s32 ddy;
    s32 ddz;
} ObjectState;

typedef struct ByteState {
    u8 pad00[0xC];
    u8 c;
    u8 d;
    u8 e;
} ByteState;

extern struct {
    s32 value;
    s32 pad[2];
} D_800814A0;

void func_80170BB0(ObjectState *obj, MotionVector *pos, ByteState *state)
{
    s32 delta;
    s32 other;
    s32 coord;
    s32 value;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 ddx;
    s32 ddy;
    s32 ddz;
    u16 timer;

    pos->x.value += obj->dx;
    pos->y.value += obj->dy;
    pos->z.value += obj->dz;

    dx = obj->dx;
    ddx = obj->ddx;
    ddy = obj->ddy;
    ddz = obj->ddz;
    do { *(volatile s32 *)&obj->dx = dx + ddx; } while (0);
    dy = obj->dy;
    dz = obj->dz;
    *(volatile s32 *)&obj->dy = dy + ddy;
    *(volatile s32 *)&obj->dz = dz + ddz;

    delta = obj->x - (other = pos->x.part.hi);
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 0x10) {
        coord = obj->y;
        other = pos->y.part.hi;
        delta = coord - other;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 0x10) {
            coord = obj->z;
            other = pos->z.part.hi;
            delta = coord - other;
            if (delta < 0) {
                delta = -delta;
            }
            if (delta < 0x10) {
                *((u16 *)obj - 1) |= 0x8000;
                D_800814A0.value = D_800814A0.value | 0x8000;
            }
        }
    }

    if (state->c < 0x80) {
        value = state->e + 8;
        state->e = value;
        state->d = value;
        state->c = value;
    }

    timer = obj->timer - 8;
    obj->timer = timer;
    if ((timer << 0x10) <= 0) {
        *((u16 *)obj - 1) |= 0x8000;
        D_800814A0.value = D_800814A0.value | 0x8000;
    }
}
