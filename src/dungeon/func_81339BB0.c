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

/* Advances motion and byte state, flagging completion near the target or when the timer expires. */
void func_80170BB0(ObjectState *obj, MotionVector *pos, ByteState *state)
{
    s32 distance;
    s32 pos_coord;
    s32 target_coord;
    s32 channel_value;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 accel_x;
    s32 accel_y;
    s32 accel_z;
    u16 remaining_time;

    pos->x.value += obj->dx;
    pos->y.value += obj->dy;
    pos->z.value += obj->dz;

    velocity_x = obj->dx;
    accel_x = obj->ddx;
    accel_y = obj->ddy;
    accel_z = obj->ddz;
    do { *(volatile s32 *)&obj->dx = velocity_x + accel_x; } while (0);
    velocity_y = obj->dy;
    velocity_z = obj->dz;
    *(volatile s32 *)&obj->dy = velocity_y + accel_y;
    *(volatile s32 *)&obj->dz = velocity_z + accel_z;

    distance = obj->x - (pos_coord = pos->x.part.hi);
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x10) {
        target_coord = obj->y;
        pos_coord = pos->y.part.hi;
        distance = target_coord - pos_coord;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 0x10) {
            target_coord = obj->z;
            pos_coord = pos->z.part.hi;
            distance = target_coord - pos_coord;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < 0x10) {
                *((u16 *)obj - 1) |= 0x8000;
                D_800814A0.value = D_800814A0.value | 0x8000;
            }
        }
    }

    if (state->c < 0x80) {
        channel_value = state->e + 8;
        state->e = channel_value;
        state->d = channel_value;
        state->c = channel_value;
    }

    remaining_time = obj->timer - 8;
    obj->timer = remaining_time;
    if ((remaining_time << 0x10) <= 0) {
        *((u16 *)obj - 1) |= 0x8000;
        D_800814A0.value = D_800814A0.value | 0x8000;
    }
}
