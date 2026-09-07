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

void func_800AC3EC(void) {
    S_800AEC8C_state *state = (S_800AEC8C_state *)&D_80083178;
    u32 angle1;
    u32 angle2;
    u32 value;

    func_800AC37C();
    angle1 = state->unkA4 >> 6;
    angle2 = state->unkA6 >> 6;
    value = state->unkB0;
    if (value & 0x3FF) {
        func_800AC1B0(
            ((s32)(((0x400 - value) & 0xFFF) - 0x400) < 0x801U) * 4,
            angle1,
            angle2);
    }
}
