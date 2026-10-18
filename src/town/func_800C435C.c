#include "common.h"
#include "shared/game_work.h"

extern s32 D_8006ADD4[];

/* Set the state halfword at offset 0xC4 to -0x240 when D_8006ADD4[0] is 0x3E000C. */
void set_state_value_when_asset_matches(void) {
    GameWork *state = &g_game_work;

    if (D_8006ADD4[0] == 0x3E000C) {
        state->view.unk_0AC = -0x240;
    }
}
