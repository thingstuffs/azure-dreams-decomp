#include "common.h"

extern u8 D_800287EC[];

void *func_80027110(s32 arg0, s32 arg1)
{
    s32 row;

    row = 2;
    if (arg0 != 0x39) {
        row = arg0;
    }
    return D_800287EC + (row * 0x41) + (arg1 * 0xD);
}
