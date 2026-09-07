#include "common.h"

typedef struct {
    u8 unk0[8];
    s32 count;
    u8 unk0c[0x34];
    s32 *base;
} State;

extern u8 D_80016000[];

void func_8059EAA0(s32 arg0) {
    State *state = *(State **)D_80016000;

    do { state->base[state->count * 2] = arg0; } while (0);
}
