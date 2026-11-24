#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

void call_service_2cc_with_zero(void) {
    town_scene_root->services->callback_2CC(0);
}
