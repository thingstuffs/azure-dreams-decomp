#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"



extern M2C_UNK D_8001BF80;


/* Pass D_8001BF80 and 0x14 to the object callback. */
void send_shared_town_record(void) {
    town_scene_root->services->callback_344(&D_8001BF80, 0x14);
}
