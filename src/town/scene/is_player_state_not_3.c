#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Returns whether the referenced record's unk_38 field differs from 3. */
s32 is_player_state_not_3(void) {
    return town_scene_root->position->unk_38 != 3;
}
