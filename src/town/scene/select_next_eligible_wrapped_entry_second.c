#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void select_next_eligible_wrapped_entry(void) {
    town_scene_root->services->callback_238(0x11, 0x200);
}
