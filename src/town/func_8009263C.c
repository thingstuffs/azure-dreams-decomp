#include "common.h"

typedef struct Box {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    s32 h;
    s32 d;
} Box;

/* Tests whether two offset boxes overlap or touch on all three axes. */
s32 func_8008FD9C(Box *box_a, Box *offset_a, Box *box_b, Box *offset_b)
{
    s32 axis_a;
    s32 axis_b;

    if ((axis_a = offset_a->x + box_a->x, axis_b = offset_b->x + box_b->x, axis_b + box_b->w >= axis_a) && axis_a + box_a->w >= axis_b &&
        (axis_a = offset_a->y + box_a->y, axis_b = offset_b->y + box_b->y, axis_b + box_b->h >= axis_a) && axis_a + box_a->h >= axis_b &&
        (axis_a = offset_a->z + box_a->z, axis_b = offset_b->z + box_b->z, axis_b + box_b->d >= axis_a) && axis_a + box_a->d >= axis_b) {
        return 1;
    }
    return 0;
}
