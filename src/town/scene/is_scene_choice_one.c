#include "common.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"

/* Returns whether scene_choice_index is 1. */
s32 is_scene_choice_one(void) {
    return scene_choice_index == 1;
}
