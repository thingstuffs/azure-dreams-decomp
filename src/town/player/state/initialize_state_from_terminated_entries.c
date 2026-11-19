#include "common.h"
#include "m2c_compat.h"
#include "town/player/position.h"
#include "town/player/state.h"
#include "town/data.h"

extern s16 D_8006ADD6;

/* Process the terminated entry list and initialize the state for the current mode. */
void initialize_state_from_terminated_entries(s32 *entries) {
    s16 mode;

    player_motion_bounds[0] = 0x1FFFFFFF;
    player_motion_bounds[2] = 0x1FFFFFFF;
    player_motion_bounds[1] = 0;
    player_motion_bounds[3] = 0;
    for (; *entries != 0; entries++) {
        expand_bounds_to_inset_rectangle(player_motion_bounds, *entries);
    }
    mode = D_8006ADD6;
    if (mode == 8) {
        player_blocking_rects[0] = 0x03000000;
        player_blocking_rects[1] = 0x04000000;
        player_blocking_rects[3] = 0x02A00000;
        player_blocking_rects[2] = 0;
        player_blocking_rects[4] = 0x80000000;
        return;
    }
    if (mode == 0xB) {
        player_blocking_rects[0] = 0;
        player_blocking_rects[1] = 0x04A00000;
        player_blocking_rects[3] = 0x03B00000;
        player_blocking_rects[2] = 0;
        player_blocking_rects[4] = 0x80000000;
        return;
    }
    player_blocking_rects[0] = 0x80000000;
}
