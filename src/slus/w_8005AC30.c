#include "common.h"

extern s16 func_8005ECF8(s32 a0);

/* Boolify a 16-bit flag/param and forward it to func_8005ECF8: returns func_8005ECF8(a0 != 0) but written as two literal-arg calls so gcc's jump-merge pass (not the sltu boolify fold) produces the shared call site. */
s16 func_8005AC30(s16 a0)
{
    if (!a0)
        return func_8005ECF8(0);
    return func_8005ECF8(1);
}
