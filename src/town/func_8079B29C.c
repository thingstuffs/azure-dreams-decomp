#include "common.h"
#include "m2c_compat.h"

extern u8 D_80016114[];
void *get_scene_entry_buffer_o(void) { return D_80016114; }
