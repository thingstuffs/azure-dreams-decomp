#include "common.h"

extern s32 town_collision_motion[];

/* Clears town_collision_motion[5] and copies source[2] to town_collision_motion[2]. */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(s32 *source) {
    town_collision_motion[5] = 0;
    town_collision_motion[2] = source[2];
}
