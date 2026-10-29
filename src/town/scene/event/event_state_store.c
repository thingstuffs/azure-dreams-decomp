#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene/entry_output.h"
#include "town/scene/event.h"

typedef struct TownStateEntry {
    u8 pad_00[0x8];
    void *unk_08;
    u8 pad_0C[0x4];
} TownStateEntry;

typedef struct TownStateEntryTable {
    u8 pad_00[0x10];
    TownStateEntry *entries;
} TownStateEntryTable;


/* In event state 5, store func_8001AA80(D_8001E950->unk_04) in the indexed entry and return 0; otherwise return 1. */
s32 in_event_state_5_store(TownStateEntryTable *table, s32 index) {
    if (town_event_state->selection_mode == 5) {
        table->entries[index].unk_08 = func_8001AA80(town_event_state->selected_entry);
        return 0;
    }
    return 1;
}
