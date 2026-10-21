/* Paged selection refresh (G00598). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B03D0, CL:town/func_800B085C. */
#include "town/shop/paged_selection_refresh_g00598.h"

/* Counts four-byte entries until an entry's second byte is zero. */
s32 count_entries_until_second_byte_zero(void *entries) {
    s32 count;
    void *entry;

    entry = entries;
    count = 0;
    if (((S_800ADFBC_0 *)entry)->unk_01 != 0) {
        do {
            entry += 4;
            count += 1;
        } while (((S_800ADFBC_0 *)entry)->unk_01 != 0);
    }
    return count;
}

/* Refresh the entry count, clamp the selection, and update five-entry page indices. */
void refresh_paged_selection_state(TownRecord *record) {
    if (record != 0) {
        if ((record->field_08 = count_entries_until_second_byte_zero((void *)record->field_20)) != 0) {
            record->field_10 = (record->field_08 - 1) / 5;
            if (record->field_04 >= record->field_08) {
                record->field_04 = record->field_08 - 1;
            }
        } else {
            record->field_04 = 0;
            record->field_10 = 0;
        }
        record->field_0C = record->field_04 / 5;
    }
}
