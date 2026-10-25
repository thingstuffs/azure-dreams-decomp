#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void call_scene_service_30c_8000(void) {
    town_scene_root->services->callback_30C(0x8000);
}
