#include "common.h"

typedef struct {
    char pad0[0xA4];
    u16 unkA4;
    u16 unkA6;
    char padA8[8];
    u16 unkB0;
} S_800AEC8C_state;

extern void func_800AC1B0(u32, u32, u32);
extern void func_800AC37C(void);

// Refreshes state and conditionally dispatches two scaled angles with an angle-range flag.
void func_800AC3EC(void) {
    S_800AEC8C_state *state = (S_800AEC8C_state *)&D_80083178;
    u32 firstScaledAngle;
    u32 secondScaledAngle;
    u32 controlAngle;

    func_800AC37C();
    firstScaledAngle = state->unkA4 >> 6;
    secondScaledAngle = state->unkA6 >> 6;
    controlAngle = state->unkB0;
    if (controlAngle & 0x3FF) {
        func_800AC1B0(
            ((s32)(((0x400 - controlAngle) & 0xFFF) - 0x400) < 0x801U) * 4,
            firstScaledAngle,
            secondScaledAngle);
    }
}
