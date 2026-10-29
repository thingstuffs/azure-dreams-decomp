#include "common.h"
#include "town/player/state.h"

extern s32 town_collision_motion[];

/* Clears town_collision_motion[4] and copies source[1] to town_collision_motion[1]. */
void clear_the_global_state_s_fifth_word_copy_source_s_second(s32 *source) {
    town_collision_motion[4] = 0;
    town_collision_motion[1] = source[1];
}
