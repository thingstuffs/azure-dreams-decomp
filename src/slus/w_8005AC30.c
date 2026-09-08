#include "common.h"

extern s16 func_8005ECF8(s32 a0);

/* Checks SPU transfer completion, waiting when requested. */
s16 func_8005AC30(s16 wait_for_completion)
{
    if (!wait_for_completion)
        return func_8005ECF8(0);
    return func_8005ECF8(1);
}
