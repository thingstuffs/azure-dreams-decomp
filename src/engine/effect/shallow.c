#include "common.h"

#include "common.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
    s16 pad;
} SVec4_80046AFC;

/* Project the line start->end onto z = target_z (result, x/y clamped to +-0x7FF0); return 1 if the line is too
 * shallow (delta z < 0x40) or the result lies more than 0x1000 from start in x or y. */
s16 func_80046AFC(SVec4_80046AFC *start, SVec4_80046AFC *end, SVec4_80046AFC *result, s16 target_z) {
    s32 delta_z;
    s32 x;
    s32 y;
    s16 clamped_x;
    s16 clamped_y;

    delta_z = end->vz - start->vz;
    if (delta_z < 0x40) {
        return 1;
    }

    x = ((end->vx - start->vx) * (target_z - end->vz)) / delta_z + end->vx;
    y = ((end->vy - start->vy) * (target_z - end->vz)) / delta_z + end->vy;

    if (x >= -0x7FF0) {
        clamped_x = 0x7FF0;
        if (x < 0x7FF1) {
            clamped_x = (s16)x;
        }
    } else {
        clamped_x = -0x7FF0;
    }
    result->vx = clamped_x;

    if (y >= -0x7FF0) {
        clamped_y = 0x7FF0;
        if (y < 0x7FF1) {
            clamped_y = (s16)y;
        }
    } else {
        clamped_y = -0x7FF0;
    }
    result->vy = clamped_y;
    result->vz = target_z;

    if (result->vx < start->vx - 0x1000) {
        return 1;
    }
    if (start->vx + 0x1000 < result->vx) {
        return 1;
    }
    if (result->vy < start->vy - 0x1000) {
        return 1;
    }
    return start->vy + 0x1000 < result->vy;
}
