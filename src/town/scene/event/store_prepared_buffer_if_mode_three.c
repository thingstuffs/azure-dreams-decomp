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

extern s32 prepare_selected_entry_buffer(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* In event state 3, store func_8001A664(D_8001E950->unk_03) in the indexed entry and return 0; otherwise return 1. */
s32 store_prepared_buffer_if_mode_three(TownStateEntryTable *table, s32 index) {
    if (town_event_state->selection_mode == 3) {
        table->entries[index].unk_08 = prepare_selected_entry_buffer(town_event_state->saved_entry);
        return 0;
    }
    return 1;
}
