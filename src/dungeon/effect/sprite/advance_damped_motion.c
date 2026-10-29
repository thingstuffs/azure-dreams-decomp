#include "common.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 xVelocity;
    s32 yVelocity;
    s32 zVelocity;
} Motion;

extern u16 sprite_effect_update_count;

/* Advance and damp motion, flagging completion when the timer expires or motion slows. */
void advance_damped_motion(void *actor, Motion *motion) {
    s32 x_velocity;
    s32 y_velocity;
    s32 speed;
    s32 y_speed;
    u16 timer;
    u16 counter;

    motion->x += motion->xVelocity;
    motion->y += motion->yVelocity;
    x_velocity = motion->xVelocity;
    y_velocity = *(s32 *)&motion->yVelocity;
    motion->z += motion->zVelocity;
    motion->xVelocity = x_velocity - ((x_velocity >> 3) + (x_velocity >> 4));
    motion->yVelocity = y_velocity - ((y_velocity >> 3) + (y_velocity >> 4));

    timer = *(u16 *)((u8 *)actor + 0x30) - 1;
    counter = sprite_effect_update_count + 1;
    ((u16 *)actor)[24] = timer;
    sprite_effect_update_count = counter;

    if ((s16)timer > 0) {
        speed = *(s16 *)((u8 *)motion + 0xE);
        y_speed = *(s16 *)((u8 *)motion + 0x12);
        speed += y_speed;
        speed = abs(speed);
        if (speed >= 4) {
            return;
        }
    }

    *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}

/* MECHANISM: Frameless leaf keeps actor/motion in $a3/$a2; the volatile y reload preserves damping
   order. A split counter RMW holds its increment in $v0 past the timer sh, filling the blez delay slot. */
