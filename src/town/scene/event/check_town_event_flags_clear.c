#include "common.h"

extern s32 func_800168C4(s32, s32);
s32 check_town_event_flags_clear(s32 arg0, s32 arg1) { return (func_800168C4(arg0, arg1) != -1); }
