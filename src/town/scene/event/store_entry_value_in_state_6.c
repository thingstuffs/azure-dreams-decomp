#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene/event.h"

typedef struct TownStateEntry {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
} TownStateEntry;

typedef struct TownStateEntryTable {
    u8 pad_00[0x10];
    TownStateEntry *entries;
} TownStateEntryTable;

extern s32 func_8001A79C(); /* Slot contract: loading images do not establish one callee contract. */

/* In event state 6, store func_8001A79C() in the indexed entry and return 0; otherwise return 1. */
s32 store_entry_value_in_state_6(TownStateEntryTable *table, s32 index) {
    if (town_event_state->selection_mode == 6) {
        table->entries[index].unk_08 = func_8001A79C();
        return 0;
    }
    return 1;
}
