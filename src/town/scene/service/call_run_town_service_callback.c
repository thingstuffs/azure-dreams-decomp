#include "town/scene.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/service.h"


/* Call set_script_flag_94c, then run town service callback 0x2F8 with (0xE, 0x200); returns 0. */
s32 call_run_town_service_callback(void) {
    set_script_flag_94c();
    town_scene_root->services->callback_2F8(0xE, 0x200);
    return 0;
}
