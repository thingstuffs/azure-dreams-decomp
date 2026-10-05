#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

/* Compute the squared distance between two 3D points. */
s32 func_8001AB20(Vec3s *point_a, Vec3s *point_b) {
    s32 diff;
    s32 total;

    diff = point_b->x;
    diff -= point_a->x;
    total = diff * diff;
    diff = point_b->y;
    diff -= point_a->y;
    total += diff * diff;
    diff = point_b->z;
    diff -= point_a->z;
    return total + diff * diff;
}
