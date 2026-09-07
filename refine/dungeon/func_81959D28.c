#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 xVelocity;
    s32 yVelocity;
    s32 zVelocity;
} Motion;

extern u16 D_800281F8;
extern s32 D_800814A0;

/* Advance and damp motion, flagging completion when the timer expires or motion slows. */
void func_81959D28(void *actor, Motion *motion) {
    s32 x_velocity;
    s32 y_velocity;
    register s32 speed ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 y_speed;
    u16 timer;
    u16 counter;

    motion->x += motion->xVelocity;
    motion->y += motion->yVelocity;
    x_velocity = motion->xVelocity;
    y_velocity = *(volatile s32 *)&motion->yVelocity;
    motion->z += motion->zVelocity;
    motion->xVelocity = x_velocity - ((x_velocity >> 3) + (x_velocity >> 4));
    motion->yVelocity = y_velocity - ((y_velocity >> 3) + (y_velocity >> 4));

    timer = *(u16 *)((u8 *)actor + 0x30) - 1;
    counter = D_800281F8 + 1;
    ASM_KEEP(counter);   /* MATCH pin: load-bearing for the whole function shape */
    *(u16 *)((u8 *)actor + 0x30) = timer;
    D_800281F8 = counter;

    if ((s16)timer > 0) {
        speed = *(s16 *)((u8 *)motion + 0xE);
        y_speed = *(s16 *)((u8 *)motion + 0x12);
        speed += y_speed;
        if (speed < 0) {
            speed = -speed;
        }
        if (speed >= 4) {
            return;
        }
    }

    *(u16 *)((u8 *)actor - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}

/* MECHANISM: Frameless leaf keeps actor/motion in $a3/$a2; the volatile y reload preserves damping order.
   A split counter RMW holds its increment in $v0 past the timer sh, filling the blez delay slot.
   Reusing pinned $v0 for the 0xE signed term, then adding the $v1 0x12 term, closes the final coloring. */
