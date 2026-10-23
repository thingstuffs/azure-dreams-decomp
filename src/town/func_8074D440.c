#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017650;
void set_scene_entry_flag_x(void) { D_80017650 = 1; }
