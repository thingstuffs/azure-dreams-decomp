#include "shared/town_event_state.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

   /* ((arg1 * 0x10) + arg0->unk_10) in store_state_selected_entry_pointer */


extern M2C_UNK D_8001F0D8;
extern M2C_UNK D_8001F18C;

typedef struct S_8001CF9C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001CF9C_0;   /* arg0 in store_state_selected_entry_pointer */

/* Store the state-selected pointer in the indexed entry. */
s32 store_state_selected_entry_pointer(S_8001CF9C_0 *table, s32 entry_index) {
    s32 *state_pointers[2];

    state_pointers[0] = &D_8001F0D8;
    state_pointers[1] = &D_8001F18C;
    ((TownEventEntryValueView *)(((entry_index * 0x10) + table->unk_10)))->unk_08 = state_pointers[D_8001E950->dispatchState];
    return 0;
}
