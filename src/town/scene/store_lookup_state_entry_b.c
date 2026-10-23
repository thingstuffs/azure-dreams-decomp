#include "shared/town_event_state.h"
#include "common.h"

   /* ((arg1 * 0x10) + arg0->unk_10) in store_lookup_in_state_7_entry */


typedef struct S_8001ADF8_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001ADF8_1;   /* arg0 in store_lookup_in_state_7_entry */


extern s32 func_8001A6D0();

/* Stores the lookup result in the selected entry when the current record has code 7. */
s32 store_lookup_in_state_7_entry(S_8001ADF8_1 *entry_table, s32 entry_index) {
    if (town_event_state->selection_mode == 7) {
        ((TownEventEntryValueView *)(((entry_index * 0x10) + entry_table->unk_10)))->value =
            func_8001A6D0(town_event_state->saved_entry);
        return 0;
    }
    return 1;
}
