#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E4C[];
extern u8 scene_state_dispatch_context[];

/* Passes the value and line to the handler with its fixed data tables. */
s32 run_event_line_handler(s32 value, s32 unused, s32 line)
{
    return func_800182E4(D_80018E4C, scene_state_dispatch_context, value, line);
}
