#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017590;
void set_scene_entry_value_a(s32 value) { D_80017590 = value; }
