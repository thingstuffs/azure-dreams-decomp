#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/event.h"

void invoke_scene_method_event_11(void) {
    town_scene_root->services->callback_238(0x11, 0x200);
}
