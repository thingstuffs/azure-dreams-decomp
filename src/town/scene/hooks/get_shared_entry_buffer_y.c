#include "slus/data.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"

/* Returns the current value of scene_string_fallback. */
void *get_shared_entry_buffer_y(void) { return scene_string_fallback; }
