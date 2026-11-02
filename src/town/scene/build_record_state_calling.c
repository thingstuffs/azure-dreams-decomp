#include "common.h"

extern s32 process_checked_entry(s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls dispatch_mode_two_by_state with object, entry_index and returns its result. */
s32 build_record_state_calling_state(s32 object, s32 entry_index) { return process_checked_entry(object, entry_index); }
