#include "common.h"
#include "m2c_compat.h"

extern u8 D_8001897D[];
/* Returns the current value of D_8001897D. */
void *process_scene_action_flag(void) { return D_8001897D; }
