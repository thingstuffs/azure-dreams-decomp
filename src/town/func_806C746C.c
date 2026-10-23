#include "common.h"
#include "m2c_compat.h"

extern s32 D_800190E0;
void set_scene_entry_flag_r(void) { D_800190E0 = 1; }
