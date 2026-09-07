#include "common.h"

#include "common.h"

extern s16 func_80053DA8(s32 a0);

s32 func_80038240(s32 a0)
{
    s32 result = 0;

    if (a0 == 0)
    {
        return result;
    }

    if (a0 == 1)
    {
        func_80053DA8(0xB4);
        return result;
    }

    func_80053DA8(0x74);
    result = 1;
    return result;
}
