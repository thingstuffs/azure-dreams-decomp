#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800197D8(s32, ...);

typedef struct S_80477B24_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80477B24_0;   /* arg0 in pass_entry_identifier_to_handler */

typedef struct S_80477B24_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80477B24_1;

/* Pass the indexed 16-byte entry and its stored value to func_800197D8. */
void pass_entry_identifier_to_handler(S_80477B24_0 *entry_table, s32 entry_index) {
    S_80477B24_1 *entry;

    entry = (entry_index * 0x10) + entry_table->unk_10;
    func_800197D8(entry->unk_0C, entry);
}
