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

extern s32 func_8001A79C();

/* In event state 4, store func_8001A79C() in the indexed entry and return 0; otherwise return 1. */
s32 store_entry_value_in_state_4(TownStateEntryTable *table, s32 index) {
    if (D_8001E950->unk_05 == 4) {
        table->entries[index].unk_08 = func_8001A79C();
        return 0;
    }
    return 1;
}
