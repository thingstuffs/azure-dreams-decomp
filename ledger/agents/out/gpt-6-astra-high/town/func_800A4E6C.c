#include "common.h"


extern s32 func_800374F4(u32);
extern void *func_8003FC64(s32);
extern u8 D_800A2690[9];


typedef struct S_800A25CC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800A25CC_0;   /* temp_s2 in func_800A25CC */

typedef struct S_800A25CC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
} S_800A25CC_1;   /* temp_s1 in func_800A25CC */

/* Allocates an object and initializes its randomized state. */
void *func_800A25CC(s32 state_value)
{
    s32 offset_sample;
    s16 initial_count;
    S_800A25CC_1 *state;
    void *object;

    object = func_8003FC64(0x136);
    if (object == 0) {
        return 0;
    }
    ((S_800A25CC_0 *)object)->unk_10 = D_800A2690;
    state = object + 0x20;
    initial_count = func_800374F4(0xB4) + 0x3C;
    state->unk_04 = initial_count;
    state->unk_06 = initial_count;
    state->unk_10 = (func_800374F4(0x28) & 0xFFFF) + 0x80;
    state->unk_14 = state_value;
    offset_sample = func_800374F4(0x40);
    state->unk_08 = offset_sample + func_800374F4(0x40) - 0x40;
    state->unk_0A = func_800374F4(0x40);
    state->unk_0C = func_800374F4(0x40);
    return object;
}

