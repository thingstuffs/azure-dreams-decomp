#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"


s32 prepare_selected_entry_buffer();
void func_8001E578();

// Updates the selected entry's value and signals the update when the state is 2.
s32 store_selected_entry_and_dispatch_402(void *entryOwner, s32 entryIndex) {
    s32 entryValue;
    s32 entriesBase;

    if (town_event_state->unk_05 == 2) {
        entryValue = prepare_selected_entry_buffer(town_event_state->unk_04);
        entriesBase = *(s32 *)((u8 *)entryOwner + 0x10);
        *(s32 *)((entryIndex << 4) + entriesBase + 8) = entryValue;
        func_8001E578(F_sbs01_pad13, entriesBase);
        return 0;
    }
    return 1;
}
