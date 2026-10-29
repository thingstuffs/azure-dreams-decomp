#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Invoke the system object callback with 0x25 and 0x200. */
void invoke_system_callback_25(void) {
    town_scene_root->services->callback_238(0x25, 0x200);
}
