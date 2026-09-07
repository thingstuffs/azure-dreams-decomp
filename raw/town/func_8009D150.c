#include "common.h"
s16 func_8009A8B0(s32 arg0, s16 arg1, s16 arg2)
{
    if (arg0 != 0) {
        u32 lt = (u32)arg1 << 16;
        return (s16)(arg1 + (((s32)arg2 - ((s32)lt >> 16)) / arg0));
    }
    return arg1;
}
