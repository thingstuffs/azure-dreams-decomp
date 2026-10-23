#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E14[];
extern u8 scene_state_dispatch_context[];

/* Call the shared handler with the two fixed tables and supplied values. */
s32 dispatch_state_dependent_actions_two(s32 input_value, s32 unused, s32 mode)
{
    return func_800182E4(D_80018E14, scene_state_dispatch_context, input_value, mode);
}
