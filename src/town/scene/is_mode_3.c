#include "common.h"
#include "town/scene.h"

extern s32 scene_choice_index;

/* Returns whether scene_choice_index is 3. */
s32 get_equals_3(void) {
    return scene_choice_index == 3;
}
