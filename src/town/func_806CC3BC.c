#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017874[];
void *get_scene_entry_buffer_l(void) { return D_80017874; }
