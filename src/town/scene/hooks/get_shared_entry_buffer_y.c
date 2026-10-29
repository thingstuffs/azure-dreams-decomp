#include "common.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"

extern u8 scene_string_fallback[];
/* Returns the current value of scene_string_fallback. */
void *get_shared_entry_buffer_y(void) { return scene_string_fallback; }
