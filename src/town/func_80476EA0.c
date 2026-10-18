#include "common.h"
#include "shared/types3b_types.h"



typedef struct {
    u16 unk0;
    u16 unk2;
} Entry4;

typedef struct {
    u8 pad0[0x20];
    s32 unk20;
    u16 unk24;
    u16 unk26;
} TownState;

extern TownIndexedValueEntry D_80016470[];
extern TownState D_800167B4;
extern Entry4 D_80016818[];

/* Copy the indexed entry value and position into the town state (returns the state pointer). */
TownState *copy_indexed_entry_to_state(s32 entry_index) {
    TownState *state = &D_800167B4;
    TownIndexedValueEntry *entries = D_80016470;
    TownIndexedValueEntry *entry = &entries[entry_index];
    Entry4 *position;

    state->unk20 = entry->value;
    position = &D_80016818[entry_index];
    state->unk24 = position->unk0;
    state->unk26 = position->unk2;
    return state;
}
