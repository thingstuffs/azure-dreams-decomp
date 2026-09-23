#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Entry12;

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

extern Entry12 D_80016470[];
extern TownState D_800167B4;
extern Entry4 D_80016818[];

/* Copy the indexed entry value and position into the town state (returns the state pointer). */
TownState *func_80017EA0(s32 entry_index) {
    TownState *state = &D_800167B4;
    Entry12 *entries = D_80016470;
    Entry12 *entry = &entries[entry_index];
    Entry4 *position;

    state->unk20 = entry->unk0;
    position = &D_80016818[entry_index];
    state->unk24 = position->unk0;
    state->unk26 = position->unk2;
    return state;
}
