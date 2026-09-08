#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001BDBC[];
extern u8 D_8001C358[];

/* Forward two values to func_80019DFC with the fixed data buffers. */
s32 func_80018338(s32 first_value, s32 unused, s32 second_value)
{
    return func_80019DFC(D_8001BDBC, D_8001C358, first_value, second_value);
}
