#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"
extern u8 D_80019040[];

void run_scene_service_218_g(void) { town_scene_root->services->callback_218(D_80019040); }
