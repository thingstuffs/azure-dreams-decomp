#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"

typedef long long s64;
typedef unsigned long long u64;



extern s32 func_8001A7E8(); /* Slot contract: loading images do not establish one callee contract. */


typedef struct S_8001AC10_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001AC10_1;   /* arg0 in store_lookup_in_state_9_entry */

   /* ((arg1 * 0x10) + ((S_8001AC10_1 *)arg0)->unk_10) in store_lookup_in_state_9_entry */

/* Store the queried value in the selected entry when the current state is 9. */
s32 store_lookup_in_state_9_entry(S_8001AC10_1 *entry_table, s32 entry_index) {
    if (town_event_state->selection_mode == 9) {
        ((TownEventEntryValueView *)(((entry_index * 0x10) + entry_table->unk_10)))->value = func_8001A7E8();
        return 0;
    }
    return 1;
}
