#include "common.h"

extern s32 checkTownEventFlagsClear(s32, s32);
s32 func_8001687C(s32 arg0, s32 arg1) { return (checkTownEventFlagsClear(arg0, arg1) != -1); }
