#include "common.h"

extern u8 D_80016000[0x10];

void func_8001A658(s32 arg0)
{
    s32 *p = *(s32 **)D_80016000;
    p = *(s32 **)((u8 *)p + 0x1C);
    *p = (arg0 + 1) * 0x10;
}
