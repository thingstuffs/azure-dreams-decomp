#include "common.h"
#include "town/map.h"
#include "town/map/state_ids_data.h"

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
} Func8008E36CInner;

typedef struct {
    Func8008E36CInner* inner;
    u8 pad4[0x60];
    s16 unk64;
    s16 index;
    void* unk68;
    void* unk6C;
} Func8008E36CArg;



extern void* town_map_state_values[];

/* Decrease the inner value, clamping it to zero and loading indexed state if negative. */
void lower_town_map_value_to_input(Func8008E36CArg* state) {
    state->inner->unkA -= 0x200;
    if (state->inner->unkA < 0) {
        state->inner->unkA = 0;
        state->unk68 = handle_town_map_input;
        state->unk64 = (s8)town_map_state_ids[state->index];
        state->unk6C = town_map_state_values[state->index];
    }
}
