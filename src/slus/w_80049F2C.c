#include "common.h"

/* Ease a struct's current x/y position (at offsets 0x28/0x2A) halfway toward
 * its target x/y (at offsets 0x4/0x6) each call: pos += (target - pos) >> 1. */
typedef struct {
    char pad0[0x4];
    s16 target_x;   /* 0x4 */
    s16 target_y;   /* 0x6 */
    char pad1[0x28 - 0x8];
    s16 x;          /* 0x28 */
    s16 y;          /* 0x2A */
} S_80049F2C;

void func_80049F2C(S_80049F2C *a0) {
    s32 dx, dy;
    dx = a0->target_x - a0->x;
    a0->x = *(volatile s16 *)&a0->x + (dx >> 1);
    dy = a0->target_y - a0->y;
    a0->y = *(volatile s16 *)&a0->y + (dy >> 1);
}
