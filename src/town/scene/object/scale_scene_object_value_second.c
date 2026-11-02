#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

/* Calls func_800194D8 with F_sbs14_pad23 and returns its result. */
s32 scale_scene_object_value(void) { return get_script_flag_mask(F_sbs14_pad23); }
