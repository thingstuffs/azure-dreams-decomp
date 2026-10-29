#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"



extern M2C_UNK D_8001C0FC;


/* Pass D_8001C0FC to the callback at offset 0x21C. */
void invoke_system_callback_21_c(void) {
    town_scene_root->services->callback_21C(&D_8001C0FC);
}
