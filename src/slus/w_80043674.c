#include "common.h"

extern s32 D_800835E8[100];
extern s32 D_80083778[3];

/* Build a cumulative cubic table with a quadratic correction after index 20, then store a fixed constant. */
void func_80043674(void)
{
    s32 cube_base;
    s32 bonus_base;
    s32 index;

    cube_base = 4;
    bonus_base = -20;
    D_800835E8[0] = 0;
    for (index = 1; index < 100; index++, cube_base++)
    {
        bonus_base++;
        D_800835E8[index] = ((u32)(cube_base * cube_base * cube_base) >> 3) + D_800835E8[index - 1];
        if (bonus_base > 0)
        {
            D_800835E8[index] = D_800835E8[index] + ((bonus_base * bonus_base) << 5);
        }
    }

    {
        s32 fixed_value = 0xFA56EA00;
        D_80083778[0] = fixed_value;
    }
}
