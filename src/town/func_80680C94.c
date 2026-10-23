#include "common.h"
#include "m2c_compat.h"

extern s32 D_800189E0;
void set_scene_entry_flag_p(void) { D_800189E0 = 1; }
