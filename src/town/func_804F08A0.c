#include "common.h"

extern s32 func_800168C4(s32, s32);
s32 checkTownEventFlagsClear(s32 arg0, s32 arg1) { return (func_800168C4(arg0, arg1) != -1); }
