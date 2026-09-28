#include "common.h"
#include "shared/game_work.h"

extern void func_800AC1B0(u32, u32, u32);
extern void func_800AC37C(void);

// Refreshes state and conditionally dispatches two scaled angles with an angle-range flag.
void func_800AC3EC(void) {
    GameView *state = &gameWork.view;
    u32 firstScaledAngle;
    u32 secondScaledAngle;
    u32 controlAngle;

    func_800AC37C();
    firstScaledAngle = ((u16)state->unk_0A4) >> 6;
    secondScaledAngle = ((u16)state->unk_0A6) >> 6;
    controlAngle = ((u16)state->viewAngle);
    if (controlAngle & 0x3FF) {
        func_800AC1B0(
            ((s32)(((0x400 - controlAngle) & 0xFFF) - 0x400) < 0x801U) * 4,
            firstScaledAngle,
            secondScaledAngle);
    }
}
