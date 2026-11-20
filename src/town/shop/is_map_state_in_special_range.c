#include "common.h"
#include "slus/map_state.h"
#include "town/shop.h"

/* Tests for maps 37 through 41 in scene 12. */
s32 is_map_state_in_special_range(void) {
    MapRuntimeState *global_state = &map_runtime_state;

    if (global_state->scene_selector == 12) {
        if ((u32)((u16)global_state->map_index - 37) < 5) {
            return 1;
        }
    }
    return 0;
}
