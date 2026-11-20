#include "common.h"
#include "slus/map_state.h"
#include "m2c_compat.h"
#include "town/player/position.h"
#include "town/player/state.h"
#include "town/data.h"


/* Process the terminated entry list and initialize the blocking bounds for the current map. */
void initialize_state_from_terminated_entries(struct TownRectangle **entries) {
    s16 map_index;

    player_motion_bounds[0] = 0x1FFFFFFF;
    player_motion_bounds[2] = 0x1FFFFFFF;
    player_motion_bounds[1] = 0;
    player_motion_bounds[3] = 0;
    for (; *entries != 0; entries++) {
        expand_bounds_to_inset_rectangle(player_motion_bounds, *entries);
    }
    map_index = map_runtime_state.map_index;
    if (map_index == 8) {
        player_blocking_rects[0] = 0x03000000;
        player_blocking_rects[1] = 0x04000000;
        player_blocking_rects[3] = 0x02A00000;
        player_blocking_rects[2] = 0;
        player_blocking_rects[4] = 0x80000000;
        return;
    }
    if (map_index == 0xB) {
        player_blocking_rects[0] = 0;
        player_blocking_rects[1] = 0x04A00000;
        player_blocking_rects[3] = 0x03B00000;
        player_blocking_rects[2] = 0;
        player_blocking_rects[4] = 0x80000000;
        return;
    }
    player_blocking_rects[0] = 0x80000000;
}
