#include "common.h"
#include "m2c_compat.h"

extern s32 D_80018BF8;
void set_scene_entry_flag_q(void) { D_80018BF8 = 1; }
