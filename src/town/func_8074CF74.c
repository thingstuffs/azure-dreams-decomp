#include "common.h"

extern s32 func_80016798(s32, s32);
s32 get_scene_result_or_fallback(s32 arg0, s32 arg1) { return (func_80016798(arg0, arg1) != -1); }
