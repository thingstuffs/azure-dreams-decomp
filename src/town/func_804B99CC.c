#include "common.h"
#include "m2c_compat.h"

extern s32 D_80018E58;
void set_scene_entry_flag_b(void) { D_80018E58 = 1; }
