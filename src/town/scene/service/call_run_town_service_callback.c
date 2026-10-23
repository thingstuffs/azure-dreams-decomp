#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_80016CC4(void);

/* Call func_80016CC4, then run town service callback 0x2F8 with (0xE, 0x200); returns 0. */
s32 call_run_town_service_callback(void) {
    func_80016CC4();
    town_scene_root->services->callback_2F8(0xE, 0x200);
    return 0;
}
