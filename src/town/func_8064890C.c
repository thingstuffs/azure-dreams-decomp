#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Return whether any of the 34 two-byte entries at +0x33A4 of the town state record holds the requested value
 * in its first byte (module-0 townRecordValueTableContains, src/town/func_80330838.c, tests the second byte). */
s32 func_8001790C(s32 target_value) {
    s32 entry_index;
    u8 *entry;

    entry = (u8 *)D_80016000->unk_38 + 0x33A4;
    for (entry_index = 0; entry_index < 34; entry_index++) {
        if (entry[0] == target_value) {
            return 1;
        }
        entry += 2;
    }
    return 0;
}
