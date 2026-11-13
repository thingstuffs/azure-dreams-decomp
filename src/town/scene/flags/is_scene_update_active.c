#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene/flags.h"

/* Returns whether scene_update_state is nonzero. */
s32 is_scene_update_active(void) {
    return scene_update_state != 0;
}
