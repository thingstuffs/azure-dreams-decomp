#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017550;
void set_scene_entry_flag_e(void) { D_80017550 = 1; }
