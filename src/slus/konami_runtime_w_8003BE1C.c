#include "common.h"

#include "common.h"

extern void *memset(void *, int, u32);

void func_8003BE1C(s16 *arg0, s32 arg1, s32 arg2)
{
    s32 sums[4];
    s32 i;
    s32 value;

    memset(sums, 0, sizeof(sums));

    for (i = 0; i < 4; i++) {
        sums[0] += arg0[i * 4];
        sums[1] += arg0[i * 4 + 1];
        sums[2] += arg0[i * 4 + 2];
    }

    sums[0] /= 4;
    sums[1] /= 4;
    sums[2] /= 4;

    for (i = 0; i < 4; i++) {
        value = ((arg0[i * 4] - sums[0]) * arg1) / arg2 + sums[0];
        if (value > 0x7FFF) {
            value = 0x7FFF;
        }
        arg0[i * 4] = value;

        value = ((arg0[i * 4 + 1] - sums[1]) * arg1) / arg2 + sums[1];
        if (value > 0x7FFF) {
            value = 0x7FFF;
        }
        arg0[i * 4 + 1] = value;

        value = ((arg0[i * 4 + 2] - sums[2]) * arg1) / arg2 + sums[2];
        if (value > 0x7FFF) {
            value = 0x7FFF;
        }
        arg0[i * 4 + 2] = value;
    }
}
