#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene.h"



extern s32 carpenter_cached_row_index;


/* Copy the linked record's unk_34 value into D_800183D4. */
void cache_player_lookup_index(void) {
    carpenter_cached_row_index = town_scene_root->position->unk_34;
}
