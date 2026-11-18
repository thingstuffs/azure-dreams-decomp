#include "common.h"
#include "town/scene/indexed_values_data.h"
#include "town/scene/state_data.h"



typedef struct {
    u16 unk0;
    u16 unk2;
} Entry4;

extern TownSceneCopiedState D_800167B4;
extern Entry4 D_80016818[];

/* Copy the indexed entry value and position into the town state (returns the state pointer). */
TownSceneCopiedState *copy_indexed_entry_to_state(s32 entry_index) {
    TownSceneCopiedState *state = &D_800167B4;
    TownIndexedValueRecord *entries = town_indexed_values;
    TownIndexedValueRecord *entry = &entries[entry_index];
    Entry4 *position;

    state->unk20 = entry->value;
    position = &D_80016818[entry_index];
    state->unk24 = position->unk0;
    state->unk26 = position->unk2;
    return state;
}
