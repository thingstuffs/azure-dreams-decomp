#include "common.h"
#include "shared/types3b_types.h"

typedef struct S_80017EF0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017EF0_0;



extern s32 copy_indexed_entry_to_state();
extern s32 D_80019BB0;
extern s32 D_80019BB4;

/* Update the indexed entry unless the current state is 3; return whether updated. */
s32 update_indexed_entry_unless_current(S_80017EF0_0 *entry_table, s32 entry_index) {
    if (D_80019BB0 != 3) {
        ((TownEventEntryValueView *)((entry_index * 0x10) + entry_table->unk_10))->unk_08 =
            copy_indexed_entry_to_state(D_80019BB4);
        return 1;
    }
    return 0;
}
