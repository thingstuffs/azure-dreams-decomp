#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019278;
void set_scene_entry_flag_m(void) { D_80019278 = 1; }
