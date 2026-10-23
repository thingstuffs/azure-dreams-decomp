#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019120;
void set_scene_entry_flag_v(void) { D_80019120 = 1; }
