#include "common.h"

#include "common.h"

extern s16 SD_Call(s32 a0);

// Dispatches nonzero modes with code 0xB4 or 0x74 and reports whether 0x74 was used.
s32 func_80038240(s32 mode)
{
    s32 result = 0;

    if (mode == 0)
    {
        return result;
    }

    if (mode == 1)
    {
        SD_Call(0xB4);
        return result;
    }

    SD_Call(0x74);
    result = 1;
    return result;
}
