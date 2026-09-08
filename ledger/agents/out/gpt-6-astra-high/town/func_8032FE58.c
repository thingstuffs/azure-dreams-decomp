#include "common.h"

extern u8 D_80016000[0x10];

/* Stores (value + 1) * 16 through the global object's pointer at offset 0x1C. */
void func_8001A658(s32 value)
{
    s32 *value_ptr = *(s32 **)D_80016000;
    value_ptr = *(s32 **)((u8 *)value_ptr + 0x1C);
    *value_ptr = (value + 1) * 0x10;
}
