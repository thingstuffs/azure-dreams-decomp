#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene/entry_output.h"


void func_8001E578(); /* Unprototyped: one or two arguments; the second register argument is ignored. */

// Updates the selected entry's value and signals the update when the state is 2.
s32 store_selected_entry_and_dispatch_402(void *entryOwner, s32 entryIndex) {
    s32 *entryValue;
    struct Entry {
        u8 pad_00[8];
        s32 *buffer;
        u8 pad_0C[4];
    };
    struct Table {
        u8 pad_00[0x10];
        struct Entry *entries;
    } *owner = entryOwner;
    struct Entry *entriesBase;

    if (town_event_state->selection_mode == 2) {
        entryValue = prepare_selected_entry_buffer(town_event_state->selected_entry);
        entriesBase = owner->entries;
        entriesBase[entryIndex].buffer = entryValue;
        func_8001E578(F_sbs01_pad13);
        return 0;
    }
    return 1;
}
