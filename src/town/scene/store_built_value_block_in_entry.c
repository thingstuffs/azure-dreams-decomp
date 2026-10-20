#include "script_symbols.h"
#include "common.h"
#include "shared/town_event_state.h"

   /* ((arg1 * 0x10) + arg0->unk_10) in store_built_value_block_in_entry */


s32 build_two_record_value_block();                                /* extern */
void func_8001E5F0(s32);                     /* extern */

typedef struct S_8001BBB4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001BBB4_0;   /* arg0 in store_built_value_block_in_entry */

/* Store the data block in the indexed entry and invoke func_8001E5F0 for 0x402. */
s32 store_built_value_block_in_entry(S_8001BBB4_0 *entry_owner, s32 entry_index) {
    ((TownEventEntryValueView *)(((entry_index * 0x10) + entry_owner->unk_10)))->unk_08 = build_two_record_value_block();
    func_8001E5F0(F_sbs01_pad13);
    return 0;
}
