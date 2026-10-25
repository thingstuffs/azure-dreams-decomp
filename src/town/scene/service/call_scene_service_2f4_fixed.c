#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void call_scene_service_2f4_fixed(void) {
    town_scene_root->services->callback_2F4(-1, -5);
}
