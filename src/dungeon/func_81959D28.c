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

void func_81959D28(void *arg0, Motion *motion) {
    s32 xVelocity;
    s32 yVelocity;
    register s32 speed ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 speedPart;
    u16 timer;
    u16 counter;

    motion->x += motion->xVelocity;
    motion->y += motion->yVelocity;
    xVelocity = motion->xVelocity;
    yVelocity = *(volatile s32 *)&motion->yVelocity;
    motion->z += motion->zVelocity;
    motion->xVelocity = xVelocity - ((xVelocity >> 3) + (xVelocity >> 4));
    motion->yVelocity = yVelocity - ((yVelocity >> 3) + (yVelocity >> 4));

    timer = *(u16 *)((u8 *)arg0 + 0x30) - 1;
    counter = D_800281F8 + 1;
    ASM_KEEP(counter);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(u16 *)((u8 *)arg0 + 0x30) = timer;
    D_800281F8 = counter;

    if ((s16)timer > 0) {
        speed = *(s16 *)((u8 *)motion + 0xE);
        speedPart = *(s16 *)((u8 *)motion + 0x12);
        speed += speedPart;
        if (speed < 0) {
            speed = -speed;
        }
        if (speed >= 4) {
            return;
        }
    }

    *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}

/* MECHANISM: Frameless leaf keeps actor/motion in $a3/$a2; the volatile y reload preserves damping order.
   A split counter RMW holds its increment in $v0 past the timer sh, filling the blez delay slot.
   Reusing pinned $v0 for the 0xE signed term, then adding the $v1 0x12 term, closes the final coloring. */
