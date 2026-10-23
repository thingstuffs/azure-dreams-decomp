#include "common.h"

extern s32 town_collision_motion[];

/* Clear the global state's fifth word and copy the source's second word. */
void clear_the_global_state_s_fifth_word_copy_source_s_second(s32 *source) {
    town_collision_motion[4] = 0;
    town_collision_motion[1] = source[1];
}
