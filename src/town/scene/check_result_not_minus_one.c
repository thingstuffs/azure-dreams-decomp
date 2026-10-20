#include "common.h"

extern s32 try_decrement_state_counter(s32, s32);
s32 check_result_not_minus_one(s32 arg0, s32 arg1) { return (try_decrement_state_counter(arg0, arg1) != -1); }
