#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018E04[];
extern u8 D_8001925C[];

/* Forward two values and the fixed data buffers to func_800181C8. */
s32 func_80614BB0(s32 first_value, s32 unused, s32 second_value)
{
    return func_800181C8(D_80018E04, D_8001925C, first_value, second_value);
}
