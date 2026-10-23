#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017560[];
void *get_scene_entry_buffer_g(void) { return D_80017560; }
