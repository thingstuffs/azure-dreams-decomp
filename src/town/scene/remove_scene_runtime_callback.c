#include "common.h"
#include "town/scene/flags.h"

extern void remove_runtime_callback(void *);
/* Calls remove_runtime_callback with clear_global_entry_flag. */
void remove_scene_runtime_callback(void) { remove_runtime_callback(clear_global_entry_flag); }
