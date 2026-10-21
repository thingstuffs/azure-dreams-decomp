#include "common.h"

extern s32 map_scene_selector_alias;

/* Returns whether D_8006ADD4 equals 0xD000C. */
s32 is_expected_movie_state(void) {
    return map_scene_selector_alias == 0xD000C;
}
