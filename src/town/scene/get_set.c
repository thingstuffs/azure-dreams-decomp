#include "common.h"
#include "town/scene.h"

extern s32 scene_choice_index;

/* Returns whether scene_choice_index is 1. */
s32 get_set_1(void) {
    return scene_choice_index == 1;
}
