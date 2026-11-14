#include "common.h"
#include "town/scene/flags.h"
#include "slus.h"
#include "town/scene.h"

/* Calls remove_runtime_callback with reset_catalog_lookup_count. */
void remove_scene_runtime_callback(void) { remove_runtime_callback(reset_catalog_lookup_count); }
