#include "script_symbols.h"
#include "common.h"

extern s32 func_800194D8(s32);
/* Calls func_800194D8 with F_sbs14_pad23 and returns its result. */
s32 scale_scene_object_value(void) { return func_800194D8(F_sbs14_pad23); }
