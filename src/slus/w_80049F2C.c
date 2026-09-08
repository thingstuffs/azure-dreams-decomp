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

/* Move the current position halfway toward the target position. */
void func_80049F2C(S_80049F2C *position) {
    s32 delta_x, delta_y;
    delta_x = position->target_x - position->x;
    position->x = *(volatile s16 *)&position->x + (delta_x >> 1);
    delta_y = position->target_y - position->y;
    position->y = *(volatile s16 *)&position->y + (delta_y >> 1);
}
