#include "common.h"
#include "town/scene/flags.h"
#include "slus.h"
#include "town/scene.h"

/* Calls remove_runtime_callback with clear_global_entry_flag. */
void remove_scene_runtime_callback(void) { remove_runtime_callback(clear_global_entry_flag); }
