#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern s32 scene_dispatch_mode_index;
/* Stores 1 in scene_dispatch_mode_index. */
void set_scene_mode_1(void) { scene_dispatch_mode_index = 1; }
