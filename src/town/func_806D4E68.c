#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void call_scene_service_zero(void) { town_scene_root->services->callback_208(0); }
