#include "common.h"
#include "town/scene.h"
#include "town/scene/progress_data.h"

/* Returns the current value of D_8001C368. */
s32 get_current_progress_value(void) {
    return scene_progress_step;
}
