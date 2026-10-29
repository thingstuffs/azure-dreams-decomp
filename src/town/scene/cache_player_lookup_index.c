#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



extern s32 D_800183D4;


/* Copy the linked record's unk_34 value into D_800183D4. */
void cache_player_lookup_index(void) {
    D_800183D4 = ((TownPositionState *)town_scene_root->position)->unk_34;
}
