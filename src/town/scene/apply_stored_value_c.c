#include "common.h"
#include "town/scene/script_hooks.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/player/state.h"

/* Pass the current value of D_8001792C to func_8001E670. */
s32 apply_stored_value_1792_c(void) {
    return get_script_flag_mask(scene_event_test_id);
}
