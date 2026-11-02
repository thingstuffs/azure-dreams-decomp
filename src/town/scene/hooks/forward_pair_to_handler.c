#include "common.h"
#include "town/scene/hooks.h"
#include "town/scene.h"

/* Calls func_800174E0 with object, entry_index and returns its result. */
s32 forward_pair_to_handler(s32 object, s32 entry_index) { return process_checked_entry(object, entry_index); }
