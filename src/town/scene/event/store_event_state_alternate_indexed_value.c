#include "common.h"
#include "shared/town_event_state.h"

typedef struct TownStateEntry {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
} TownStateEntry;

typedef struct TownStateEntryTable {
    u8 pad_00[0x10];
    TownStateEntry *entries;
} TownStateEntryTable;

extern s32 func_8001ABB4();

/* In event state 6, store func_8001ABB4() in the indexed entry and return 0; otherwise return 1. */
s32 store_event_state_6_alternate_indexed_value(TownStateEntryTable *table, s32 index) {
    if (town_event_state->unk_05 == 6) {
        table->entries[index].unk_08 = func_8001ABB4();
        return 0;
    }
    return 1;
}
