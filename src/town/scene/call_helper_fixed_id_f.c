#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A64C with F_bar_pad02 and returns its result. */
s32 get_script_flag_bar_pad02(void) { return get_script_flag_mask(F_bar_pad02); }
