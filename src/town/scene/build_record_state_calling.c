#include "common.h"

extern s32 dispatch_mode_two_by_state(s32, s32);
s32 build_record_state_calling_state(s32 object, s32 entry_index) { return dispatch_mode_two_by_state(object, entry_index); }
