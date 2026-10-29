#include "common.h"
#include "town/scene/hooks.h"

extern s32 func_800174E0(s32, s32);
/* Calls func_800174E0 with object, entry_index and returns its result. */
s32 forward_pair_to_handler(s32 object, s32 entry_index) { return func_800174E0(object, entry_index); }
