#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



/* Return whether the referenced record's unk_38 field is nonzero. */
s32 is_player_state_nonzero(void) {
    return ((TownPositionState *)town_scene_root->position)->unk_38 != 0;
}
