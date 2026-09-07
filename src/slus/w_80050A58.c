#include "common.h"

#include "common.h"

extern u8 D_8002E950[];

void func_80050A58(s32 *arg0, s32 *arg1)
{
    s32 i;
    u32 temp;
    u32 div;
    s32 table;

    i = 0;
    table = (s32)D_8002E950;
    do {
        temp = *(u8 *)(i + table);
        div = temp / 21;

        *(s32 *)(arg0[i] + 8) = arg1[(u8)div] + ((u8)(temp - (div * 21)) * 12);
        i++;
    } while (i < 17);
}
