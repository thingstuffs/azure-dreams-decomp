#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017AAC;
void set_scene_entry_flag_g(void) { D_80017AAC = 1; }
