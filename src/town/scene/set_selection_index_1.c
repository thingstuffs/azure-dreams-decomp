#include "common.h"
#include "m2c_compat.h"

extern s32 scene_selection_index;
/* Stores 1 in scene_selection_index. */
void set_selection_index_1(void) { scene_selection_index = 1; }
