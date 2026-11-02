#include "common.h"
#include "town/scene.h"

/* Calls func_80017D48 with object, entry_index and returns its result. */
s32 query_state_with_selector_10(s32 object, s32 entry_index) { return process_checked_entry(object, entry_index); }
