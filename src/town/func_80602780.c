#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017FC8;
void set_scene_entry_flag_l(void) { D_80017FC8 = 1; }
