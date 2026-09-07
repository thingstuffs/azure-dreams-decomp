#include "common.h"

#define FIELD(base, type, offset) (*(type *)((base) + (offset)))

extern u16 func_800A2B28();
extern u8 D_80083460[0x14];

s16 func_800A2B5C(s32 arg0) {
    u8 *state = D_80083460;
    s32 current = FIELD(state, s32, 0xC);

    if (current == arg0) {
        goto call;
    }
    if (current != 0) {
        return 1;
    }
    if (FIELD(state, s32, 0x10) != 0) {
        return 1;
    }
    if (FIELD(state, s16, 0xA) != 0) {
        return 1;
    }
    if (FIELD(state, u16, 2) & 8) {
        return 1;
    }
    FIELD(state, s32, 0xC) = arg0;
call:
    return func_800A2B28();
}
