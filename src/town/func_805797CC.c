#include "common.h"

extern s32 decrement_state_counter(s32, s32);
s32 func_800167CC(s32 arg0, s32 arg1) { return (decrement_state_counter(arg0, arg1) != -1); }
