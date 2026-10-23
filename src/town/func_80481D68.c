#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019550;
void set_scene_entry_flag_a(void) { D_80019550 = 1; }
