#include "common.h"

#include "common.h"

extern s32 func_8003C5A4(s32 arg0);

u32 *func_8003C8E4(s32 arg0)
{
    s32 index;

    index = func_8003C5A4(arg0);
    if (index >= 0) {
        return (u32 *)(0x800135C4 + (index << 2));
    }
    return 0;
}
