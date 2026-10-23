#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019B98;
void set_scene_entry_flag_k(void) { D_80019B98 = 1; }
