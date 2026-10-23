#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017B40;
void set_scene_entry_value_f(s32 value) { D_80017B40 = value; }
