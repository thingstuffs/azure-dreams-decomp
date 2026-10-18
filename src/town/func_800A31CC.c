#include "modules/town_door.h"

/* Decrement the countdown and switch to advance_door_close_angle when it expires. */
void tick_door_open_countdown(S_800A092C_0 *state) {
    u16 countdown;

    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        state->unk_50 = &advance_door_close_angle;
    }
}
