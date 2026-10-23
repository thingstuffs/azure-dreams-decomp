#include "common.h"
#include "m2c_compat.h"

extern s32 D_8001B178;
void set_scene_entry_flag_w(void) { D_8001B178 = 1; }
