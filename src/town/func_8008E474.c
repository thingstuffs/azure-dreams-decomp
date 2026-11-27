/* Recovered retail twin. */
#include "common.h"
#include "town/map.h"
#include "town/map/state_ids_data.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
} Func8008E3F0Inner;

typedef struct {
    Func8008E3F0Inner* inner;
    u8 pad4[0x60];
    s16 timer;
    s16 index;
    void* update;
    void* next_update;
} Func8008E3F0Arg;



extern void* town_map_state_values[];

/*
 * Subtracts 0x200 from the inner field at offset 8; once negative, clamps it to zero and restores
 * the callback and indexed state values.
 */
void lower_town_map_value_and_resume_input(Func8008E3F0Arg* state) {
    state->inner->unk8 -= 0x200;
    if (state->inner->unk8 < 0) {
        state->inner->unk8 = 0;
        state->update = handle_town_map_input;
        state->timer = (s8)town_map_state_ids[state->index];
        state->next_update = town_map_state_values[state->index];
    }
}
