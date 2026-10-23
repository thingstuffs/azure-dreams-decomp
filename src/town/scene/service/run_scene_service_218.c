#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern u8 D_800178A4[];

void run_scene_service_218(void) { town_scene_root->services->callback_218(D_800178A4); }
