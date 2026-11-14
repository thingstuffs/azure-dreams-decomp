#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/player.h"



/* Returns the field at offset 0x2D60 in the record linked through D_80016000. */
s32 get_town_state_count(void) {
    return town_scene_root->town_state->unk_2D60;
}
