#include "common.h"

extern s32 func_80017D48(s32, s32);
/* Calls func_80017D48 with object, entry_index and returns its result. */
s32 query_state_with_selector_10(s32 object, s32 entry_index) { return func_80017D48(object, entry_index); }
