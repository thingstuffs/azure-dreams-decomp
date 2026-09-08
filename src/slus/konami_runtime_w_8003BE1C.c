#include "common.h"

#include "common.h"

extern void *memset(void *, int, u32);

/* Scale four XYZ points about their center, capping coordinates at 0x7FFF. */
void func_8003BE1C(s16 *points, s32 scale_num, s32 scale_den)
{
    s32 center[4];
    s32 point_idx;
    s32 coord;

    memset(center, 0, sizeof(center));

    for (point_idx = 0; point_idx < 4; point_idx++) {
        center[0] += points[point_idx * 4];
        center[1] += points[point_idx * 4 + 1];
        center[2] += points[point_idx * 4 + 2];
    }

    center[0] /= 4;
    center[1] /= 4;
    center[2] /= 4;

    for (point_idx = 0; point_idx < 4; point_idx++) {
        coord = ((points[point_idx * 4] - center[0]) * scale_num) / scale_den + center[0];
        if (coord > 0x7FFF) {
            coord = 0x7FFF;
        }
        points[point_idx * 4] = coord;

        coord = ((points[point_idx * 4 + 1] - center[1]) * scale_num) / scale_den + center[1];
        if (coord > 0x7FFF) {
            coord = 0x7FFF;
        }
        points[point_idx * 4 + 1] = coord;

        coord = ((points[point_idx * 4 + 2] - center[2]) * scale_num) / scale_den + center[2];
        if (coord > 0x7FFF) {
            coord = 0x7FFF;
        }
        points[point_idx * 4 + 2] = coord;
    }
}
