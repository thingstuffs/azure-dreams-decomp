#include "common.h"
#include "town/shop.h"
#include "town/shop/state.h"

typedef struct {
    s8 pad00[4];
    s32 unk04;
    s8 pad08[0x10];
    s32 unk18;
    s8 pad1C[4];
    u8 *unk20;
} UnkStruct800B023C;

/* Checks whether the entry bypasses the limit or its combined value is below 20. */
s32 check_entry_limit_or_combined_value(UnkStruct800B023C *entry) {
    s32 total;

    if (entry->unk18 == 0) {
        if ((u32) (entry->unk20[(entry->unk04 * 4) + 1] - 0x17) < 2U) {
            return 1;
        }
        total = count_nonzero_fixed_table_words();
        total += count_entries_with_flag_20(entry->unk20);
        return total < 20;
    }
    return 1;
}
