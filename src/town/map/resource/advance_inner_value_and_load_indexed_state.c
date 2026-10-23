#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
} Func8008E3F0Inner;

typedef struct {
    Func8008E3F0Inner* inner;
    u8 pad4[0x60];
    s16 unk64;
    s16 index;
    void* unk68;
    void* unk6C;
} Func8008E3F0Arg;

extern u8 D_8008BC58[];
extern u8 town_map_state_ids[];
extern void* town_map_state_values[];

/* Advance the inner value by 0x200, clamping and loading indexed state when positive. */
void advance_inner_value_and_load_indexed_state(Func8008E3F0Arg* state) {
    state->inner->unk8 += 0x200;
    if (state->inner->unk8 > 0) {
        state->inner->unk8 = 0;
        state->unk68 = D_8008BC58;
        state->unk64 = (s8)town_map_state_ids[state->index];
        state->unk6C = town_map_state_values[state->index];
    }
}
