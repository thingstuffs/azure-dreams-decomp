#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Run town service callback 0x280 with the code plus flag 0x1000. */
void dispatch_flagged_command(s32 code) {
    town_scene_root->services->callback_280(code | 0x1000);
}
