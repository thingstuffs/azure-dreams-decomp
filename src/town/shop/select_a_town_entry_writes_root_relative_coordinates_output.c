#include "common.h"

typedef struct TownEntry {
    u8 pad0[0x10];
    u16 x;
    u16 y;
} TownEntry;

typedef struct TownEntryOwner {
    u32 pad0;
    TownEntry *entries;
} TownEntryOwner;

typedef struct TownRoot {
    u16 x;
    u16 y;
    u8 pad4[8];
    TownEntryOwner *owner;
} TownRoot;

typedef struct TownOutputHalf {
    u16 low;
    u16 coordinate;
} TownOutputHalf;

typedef struct TownOutput {
    u32 first;
    u32 second;
    u32 third;
} TownOutput;

extern TownRoot *town_script_state_slots[];
extern TownOutput shop_target_position;
extern s32 D_80100B68;

/* Selects a town entry and writes its root-relative coordinates to the output. */
s32 select_a_town_entry_writes_root_relative_coordinates_output(s32 entryIndex) {
    TownRoot *root = town_script_state_slots[0];
    TownEntry *entry;
    TownEntry *entries;
    TownOutput *output;
    TownEntryOwner *owner;
    u32 rootX;
    u16 rootY;
    u32 entryX;
    u16 entryY;
    u32 entryOffsetOrAddress;
    s32 selectedEntryIndex = entryIndex;

    D_80100B68 = selectedEntryIndex;
    entryOffsetOrAddress = selectedEntryIndex * sizeof(TownEntry);
    owner = root->owner;
    entries = owner->entries;
    rootX = root->x;
    rootY = root->y;
    shop_target_position.first = 0;
    entryOffsetOrAddress += (u32)entries;
    entry = (TownEntry *)entryOffsetOrAddress;
    entryX = entry->x;
    output = &shop_target_position;
    output->second = 0;
    entryX += rootX;
    ((TownOutputHalf *)&output->first)->coordinate = entryX;
    entryY = entry->y;
    ((TownOutputHalf *)&output->second)->coordinate = entryY + rootY;
    output->third = 0xFFE00000;
    return selectedEntryIndex;
}
