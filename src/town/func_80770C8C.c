#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017C84;
void set_scene_entry_flag_z(void) { D_80017C84 = 1; }
