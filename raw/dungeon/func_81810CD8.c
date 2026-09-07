#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

void func_80025CD8(void *arg0) {
    volatile s32 zero[1];
    s32 saved;

    zero[0] = 0;
    FIELD(arg0, s8, 1) = 0x28;
    saved = zero[0];
    FIELD(arg0, s8, 2) = -0x18;
    FIELD(arg0, s8, 3) = 4;
    FIELD(arg0, s8, 0xA) = 0x30;
    FIELD(arg0, s8, 0xB) = 0x58;
    FIELD(arg0, s32, 4) = saved;
    FIELD(arg0, u8, 0) |= 0x80;
}
