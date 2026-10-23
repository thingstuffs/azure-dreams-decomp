#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void clear_scene_service_value(void) { town_scene_root->services->callback_208(0); }
