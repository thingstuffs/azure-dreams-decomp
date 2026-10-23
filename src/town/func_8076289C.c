#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017B74;
void set_scene_entry_flag_y(void) { D_80017B74 = 1; }
