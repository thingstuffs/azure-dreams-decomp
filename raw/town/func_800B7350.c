#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_800786DC[];
extern u8 D_800786E8[];

void func_800B4AB0(void *arg0)
{
    void *state;

    if (FIELD(FIELD(arg0, void *, 0), s32, 0x2C) > 0) {
        *FIELD(FIELD(arg0, void *, 0x5C), void **, 0x98) = D_800786DC;
        FIELD(arg0, s32, 0xC) = FIELD(arg0, s32, 0xC) & -3;
    } else {
        *FIELD(FIELD(arg0, void *, 0x5C), void **, 0x98) = 0;
        FIELD(arg0, s32, 0xC) = FIELD(arg0, s32, 0xC) | 2;
    }

    state = FIELD(arg0, void *, 0);
    if (FIELD(state, s32, 0x2C) < FIELD(state, s32, 0x30)) {
        FIELD(arg0, s32, 0xC) = FIELD(arg0, s32, 0xC) & -2;
        *FIELD(FIELD(arg0, void *, 0x5C), void **, 0x9C) = D_800786E8;
    } else {
        FIELD(arg0, s32, 0xC) = FIELD(arg0, s32, 0xC) | 1;
        *FIELD(FIELD(arg0, void *, 0x5C), void **, 0x9C) = 0;
    }
}
