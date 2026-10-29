#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"

/* Invoke the scene service at offset 0x280 with request 0x1704. */
void invoke_scene_service(void) {
    town_scene_root->services->callback_280(0x1704);
}
