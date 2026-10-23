#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017638[];
void *get_scene_entry_buffer_m(void) { return D_80017638; }
