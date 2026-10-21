#include "common.h"

extern u8 D_800133A6;
extern s32 player_motion_bounds[4];
extern s32 player_blocking_rects[33];

/* Initializes the state tables with an extra entry for mode 10. */
void initialize_mode_state_tables(void) {
    u8 *mode_page;

    player_motion_bounds[0] = 0x025FFFFF;
    player_motion_bounds[2] = 0x01000000;
    player_motion_bounds[1] = 0x1DA00000;
    player_motion_bounds[3] = 0x1DA00000;
    player_blocking_rects[0] = 0xF0000000;
    player_blocking_rects[1] = 0x0FE00000;
    player_blocking_rects[2] = 0;
    player_blocking_rects[3] = 0x04000000;
    player_blocking_rects[4] = 0x10200000;
    player_blocking_rects[5] = 0x30000000;
    player_blocking_rects[6] = 0;
    player_blocking_rects[7] = 0x04000000;
    player_blocking_rects[8] = 0xF0000000;
    player_blocking_rects[9] = 0x0F500000;
    player_blocking_rects[10] = 0;
    player_blocking_rects[11] = 0x065FFFFF;
    player_blocking_rects[12] = 0x10B00000;
    player_blocking_rects[13] = 0x30000000;
    player_blocking_rects[14] = 0;
    player_blocking_rects[15] = 0x065FFFFF;
    player_blocking_rects[16] = 0xF0000000;
    player_blocking_rects[17] = 0x0F980000;
    player_blocking_rects[18] = 0x05E80000;
    player_blocking_rects[19] = 0x065FFFFF;
    player_blocking_rects[20] = 0x10680000;
    player_blocking_rects[21] = 0x30000000;
    player_blocking_rects[22] = 0x05E80000;
    player_blocking_rects[23] = 0x065FFFFF;
    player_blocking_rects[24] = 0x1A100000;
    player_blocking_rects[25] = 0x30000000;
    player_blocking_rects[26] = 0;
    player_blocking_rects[27] = 0x09EFFFFF;
    mode_page = (u8 *)0x80010000;
    if (mode_page[0x33A6] == 0xA) {
        player_blocking_rects[29] = 0x05F00000;
        player_blocking_rects[28] = 0xF0000000;
        player_blocking_rects[30] = 0;
        player_blocking_rects[31] = 0x09EFFFFF;
        player_blocking_rects[32] = 0x80000000;
    } else {
        player_blocking_rects[28] = 0x80000000;
    }
}
