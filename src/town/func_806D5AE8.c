#include "common.h"
#include "m2c_compat.h"

extern s32 D_80018BAC;
void set_scene_entry_flag_u(void) { D_80018BAC = 1; }
