#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

s32 func_8001AB20(Vec3s *arg0, Vec3s *arg1) {
    s32 diff;
    s32 total;

    diff = arg1->x;
    diff -= arg0->x;
    total = diff * diff;
    do {
        diff = arg1->y;
        diff -= arg0->y;
    } while (0);
    total += diff * diff;
    do {
        diff = arg1->z;
        diff -= arg0->z;
    } while (0);
    return total + diff * diff;
}
