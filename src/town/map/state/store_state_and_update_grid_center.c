#include "shared/runtime_dispatch.h"
#include "common.h"

extern u8 town_map_selection_state[12];

extern void request_scene_state_with_parameters(s32 a0, s16 a1, s16 a2, s16 a3, s32 a4);

/* Store the state and issue an update at the grid cell center using the alternate buffer. */
void store_state_and_update_grid_center(s8 state) {
    town_map_selection_state[6] = state;
    request_scene_state_with_parameters(0xC, ((town_map_selection_state[0] + 1) << 6) | 0x20, ((town_map_selection_state[1] + 1) << 6) | 0x20, -0x100, runtime_dispatch_state.flags16 ^ 1);
}
