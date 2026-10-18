#include "shared/object_node.h"
#include "common.h"


extern s32 scale_random_to_unsigned_halfword_limit(u32);
extern u8 D_800A2690[9];


typedef struct S_800A25CC_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800A25CC_0;

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
} S_800A25CC_1;

/* Allocates an object and initializes its randomized state. */
void *allocate_randomized_effect_object(s32 state_value)
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
    initial_count = scale_random_to_unsigned_halfword_limit(0xB4) + 0x3C;
    state->unk_04 = initial_count;
    state->unk_06 = initial_count;
    state->unk_10 = (scale_random_to_unsigned_halfword_limit(0x28) & 0xFFFF) + 0x80;
    state->unk_14 = state_value;
    offset_sample = scale_random_to_unsigned_halfword_limit(0x40);
    state->unk_08 = offset_sample + scale_random_to_unsigned_halfword_limit(0x40) - 0x40;
    state->unk_0A = scale_random_to_unsigned_halfword_limit(0x40);
    state->unk_0C = scale_random_to_unsigned_halfword_limit(0x40);
    return object;
}

