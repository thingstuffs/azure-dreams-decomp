#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017670;
void run_scene_callbacks_with_value_shift(s32 value) { D_80017670 = value; }
