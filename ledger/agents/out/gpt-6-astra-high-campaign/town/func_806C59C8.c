#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E3C[];
extern u8 D_800190B4[];

/* Call the shared handler with the two fixed tables and supplied values. */
s32 func_800169C8(s32 input_value, s32 unused, s32 mode)
{
    return func_800182E4(D_80018E3C, D_800190B4, input_value, mode);
}
