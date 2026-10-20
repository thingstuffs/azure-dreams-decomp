#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Return whether any of the 34 two-byte entries at +0X33A4 of the town state record holds the requested value
 * in byte 0 (this module's copy of record_value_table_contains, src/town/func_80330838.c, which tests byte 1). */
s32 record_value_table_contains_first_byte(s32 target_value) {
    s32 entry_index;
    u8 *entry;

    entry = (u8 *)D_80016000->unk_38 + 0X33A4;
    for (entry_index = 0; entry_index < 34; entry_index++) {
        if (entry[0] == target_value) {
            return 1;
        }
        entry += 2;
    }
    return 0;
}
