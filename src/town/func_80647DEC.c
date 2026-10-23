#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017B44;
void set_scene_entry_flag_o(void) { D_80017B44 = 1; }
