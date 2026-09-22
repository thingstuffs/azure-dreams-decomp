#include "common.h"
extern u8 D_8006E240[];

extern s32 func_8004A658(s32, s32);

/* Resolve the item's description: kind 0x12 uses the fixed table, everything else is looked up. */
s32 func_800A7A38(u8 *item)
{
    s32 result;

    if (item[1] == 0x12) {

        result = D_8006E240;
    } else {
        result = func_8004A658(item[1], item[0]);
    }
    return result;
}
