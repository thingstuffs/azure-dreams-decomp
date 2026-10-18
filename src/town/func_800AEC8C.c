#include "common.h"
#include "shared/game_work.h"

extern void count_flagged_tiles_along_direction(u32, u32, u32);
extern void clear_flagged_cells_and_reset_list(void);

// Refreshes state and conditionally dispatches two scaled angles with an angle-range flag.
void refresh_state_and_dispatch_angles(void) {
    GameView *state = &g_game_work.view;
    u32 firstScaledAngle;
    u32 secondScaledAngle;
    u32 controlAngle;

    clear_flagged_cells_and_reset_list();
    firstScaledAngle = ((u16)state->unk_0A4) >> 6;
    secondScaledAngle = ((u16)state->unk_0A6) >> 6;
    controlAngle = ((u16)state->viewAngle);
    if (controlAngle & 0x3FF) {
        count_flagged_tiles_along_direction(
            ((s32)(((0x400 - controlAngle) & 0xFFF) - 0x400) < 0x801U) * 4,
            firstScaledAngle,
            secondScaledAngle);
    }
}
