#include "common.h"

extern u8 D_80080B18[];
u8 D_80080B1B = 0;
u8 D_80080B1C = 0;

u8 func_80048DA0(s32 index, s32 count)
{
    u8 *table;

    D_80080B1B = count + 5;
    table = D_80080B18;
    D_80080B1C = (count * 2) + 5;
    return table[index];
}
