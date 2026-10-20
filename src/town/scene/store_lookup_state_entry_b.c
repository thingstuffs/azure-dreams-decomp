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
    if (D_8001E950->unk_05 == 7) {
        ((TownEventEntryValueView *)(((entry_index * 0x10) + entry_table->unk_10)))->unk_08 =
            func_8001A6D0(D_8001E950->unk_03);
        return 0;
    }
    return 1;
}
