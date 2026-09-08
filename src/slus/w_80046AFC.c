#include "common.h"

#include "common.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
} SVec3;

/* Project the line through two points to target_z, clamp x/y, and return 1 if depth or range checks fail. */
s32 func_80046AFC(SVec3 *start, SVec3 *end, SVec3 *result, s32 target_z) {
    SVec3 *out; /* t2 */
    register s32 output_z ASM_REG("$11");  /* t3 */
    s32 delta_z;
    s32 z_offset;
    s32 x;
    s32 y;
    s16 clamped_x;
    s16 clamped_y;

    out = result;
    output_z = target_z;

    delta_z = end->vz - start->vz;
    if (delta_z < 0x40) {
        return 1;
    }

    z_offset = (s16)target_z - end->vz;
    x = ((end->vx - start->vx) * z_offset) / delta_z + end->vx;
    y = ((end->vy - start->vy) * z_offset) / delta_z + end->vy;

    clamped_x = -0x7FF0;
    if (x >= -0x7FF0) {
        clamped_x = 0x7FF0;
        if (x < 0x7FF1) {
            clamped_x = (s16)x;
        }
    }
    out->vx = clamped_x;

    if (y >= -0x7FF0) {
        clamped_y = 0x7FF0;
        if (y < 0x7FF1) {
            clamped_y = (s16)y;
        }
    } else {
        clamped_y = -0x7FF0;
    }
    out->vy = clamped_y;
    out->vz = output_z;

    if (out->vx < start->vx - 0x1000) {
        return 1;
    }
    if (start->vx + 0x1000 < out->vx) {
        return 1;
    }
    {
        s32 output_y;
        output_y = out->vy;
        if (output_y < start->vy - 0x1000) {
            return 1;
        }
        return start->vy + 0x1000 < output_y;
    }
}
