#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017620;
void set_scene_entry_flag_f(void) { D_80017620 = 1; }
