#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017488;
void set_scene_entry_flag_t(void) { D_80017488 = 1; }
