#include "common.h"
#include "m2c_compat.h"

extern u8 scene_string_fallback[];
void *get_shared_entry_buffer_y(void) { return scene_string_fallback; }
