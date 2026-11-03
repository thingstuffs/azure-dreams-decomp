#include "common.h"
#include "shared/entity.h"
#include "town/player.h"

extern s32 town_collision_motion[];

/* Clears town_collision_motion[5] and copies source[2] to town_collision_motion[2]. */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(ObjectPosition *source) {
    town_collision_motion[5] = 0;
    town_collision_motion[2] = source->z.v;
}
