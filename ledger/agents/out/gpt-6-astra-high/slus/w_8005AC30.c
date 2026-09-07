#include "common.h"

extern s16 func_8005ECF8(s32 a0);

/* Forward whether flag is nonzero to func_8005ECF8 and return its result. */
s16 func_8005AC30(s16 flag)
{
    if (!flag)
        return func_8005ECF8(0);
    return func_8005ECF8(1);
}
