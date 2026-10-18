#include "common.h"

extern s32 dispatch_mode_two_by_state(s32, s32);
s32 build_record_state_calling_state(s32 arg0, s32 arg1) { return dispatch_mode_two_by_state(arg0, arg1); }
