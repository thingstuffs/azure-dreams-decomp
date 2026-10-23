#include "common.h"
#include "m2c_compat.h"

extern s32 scene_dispatch_mode_index;
/* Stores 2 in scene_dispatch_mode_index. */
void store_supplied_values(void) { scene_dispatch_mode_index = 2; }
