#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019150;
void set_scene_entry_flag_j(void) { D_80019150 = 1; }
