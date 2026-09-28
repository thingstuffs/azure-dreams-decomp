#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 unk0[8];
    s32 count;
    u8 unk0c[0x34];
    s32 *base;
} State;


/* Store the value in the first word of the current state entry. */
void func_8059EAA0(s32 value) {
    State *state = *(State **)((u8 *)(&D_80016000));

    state->base[state->count * 2] = value;
}
