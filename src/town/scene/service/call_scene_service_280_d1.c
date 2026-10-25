#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void call_scene_service_280_d1(void) {
    town_scene_root->services->callback_280(0xD1);
}
