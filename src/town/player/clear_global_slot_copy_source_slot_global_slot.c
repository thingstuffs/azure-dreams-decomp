#include "common.h"

extern s32 town_collision_motion[];

/* Clear global slot 5 and copy source slot 2 into global slot 2. */
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(s32 *source) {
    town_collision_motion[5] = 0;
    town_collision_motion[2] = source[2];
}
