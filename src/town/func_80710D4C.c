#include "common.h"
#include "m2c_compat.h"
#include "town.h"

extern s32 D_8001B178;
void set_scene_entry_flag_w(void) { D_8001B178 = 1; }
