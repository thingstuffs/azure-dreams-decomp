#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A64C with F_bar_pad01 and returns its result. */
s32 call_helper_with_fixed_id_0x118b(void) { return get_script_flag_mask(F_bar_pad01); }
