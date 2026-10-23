#include "common.h"
#include "m2c_compat.h"

extern s32 D_800175C0;
void set_scene_entry_flag_i(void) { D_800175C0 = 1; }
