#include "common.h"

extern s32 func_800167CC(s32, s32);
s32 check_result_not_minus_one(s32 arg0, s32 arg1) { return (func_800167CC(arg0, arg1) != -1); }
