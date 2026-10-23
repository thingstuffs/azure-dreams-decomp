#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"




/* Invoke the callback at offset 0x30C with value 0x9000. */
void invoke_callback_30_c_9000(void) {
    town_scene_root->services->callback_30C(0x9000);
}
