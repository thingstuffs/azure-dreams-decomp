#include "common.h"

#include "common.h"

typedef struct {
    s16 vx;
    s16 vy;
    s16 vz;
} SVec3;

s32 func_80046AFC(SVec3 *arg0, SVec3 *arg1, SVec3 *arg2, s32 arg3) {
    register SVec3 *out ASM_REG("$10"); /* t2 */
    register s32 z_arg ASM_REG("$11");  /* t3 */
    s32 dz;
    s32 factor;
    s32 x;
    s32 y;
    s16 cx;
    s16 cy;

    out = arg2;
    z_arg = arg3;

    dz = arg1->vz - arg0->vz;
    if (dz < 0x40) {
        return 1;
    }

    factor = (s16)arg3 - arg1->vz;
    x = ((arg1->vx - arg0->vx) * factor) / dz + arg1->vx;
    y = ((arg1->vy - arg0->vy) * factor) / dz + arg1->vy;

    cx = -0x7FF0;
    if (x >= -0x7FF0) {
        cx = 0x7FF0;
        if (x < 0x7FF1) {
            cx = (s16)x;
        }
    }
    out->vx = cx;

    if (y >= -0x7FF0) {
        cy = 0x7FF0;
        if (y < 0x7FF1) {
            cy = (s16)y;
        }
    } else {
        cy = -0x7FF0;
    }
    out->vy = cy;
    out->vz = z_arg;

    if (out->vx < arg0->vx - 0x1000) {
        return 1;
    }
    if (arg0->vx + 0x1000 < out->vx) {
        return 1;
    }
    {
        register s32 oy ASM_REG("$6");
        oy = out->vy;
        if (oy < arg0->vy - 0x1000) {
            return 1;
        }
        return arg0->vy + 0x1000 < oy;
    }
}
