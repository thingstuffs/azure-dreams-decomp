#include "common.h"
#include "shared/game_work.h"

extern s32 D_8006ADD4[];

/* Set the state halfword at offset 0xC4 to -0x240 when D_8006ADD4[0] is 0x3E000C. */
void func_800C1ABC(void) {
    GameWork *state = &gameWork;

    if (D_8006ADD4[0] == 0x3E000C) {
        state->unk_0C4 = -0x240;
    }
}
