#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Returns whether the referenced record's unk_38 value differs from 1. */
s32 is_player_state_not_1(void) {
    return ((TownPositionState *)town_scene_root->position)->unk_38 != 1;
}
