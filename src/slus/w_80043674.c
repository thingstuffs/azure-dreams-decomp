#include "common.h"

/* Build a cumulative table of (n^3)/8 with a correction term of (m^2*32) added
 * once m=(i-20) becomes positive (m runs from -19 up to 79 as n runs 5..103,
 * i runs 1..99). Then stash an unrelated constant into D_80083778. */
extern s32 D_800835E8[100];
extern s32 D_80083778[3];

void func_80043674(void)
{
    s32 n;
    s32 m;
    s32 i;

    n = 4;
    m = -20;
    D_800835E8[0] = 0;
    for (i = 1; i < 100; i++, n++)
    {
        m++;
        D_800835E8[i] = ((u32)(n * n * n) >> 3) + D_800835E8[i - 1];
        if (m > 0)
        {
            D_800835E8[i] = D_800835E8[i] + ((m * m) << 5);
        }
    }

    {
        s32 tmp = 0xFA56EA00;
        D_80083778[0] = tmp;
    }
}
