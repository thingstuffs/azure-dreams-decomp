#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E578(s32, ...);

typedef struct S_8046C8C4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8046C8C4_0;   /* arg0 in pass_indexed_entry */

typedef struct S_8046C8C4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8046C8C4_1;

/* Pass the indexed entry and its identifier to the handler. */
void pass_indexed_entry(S_8046C8C4_0 *table, s32 entry_index) {
    S_8046C8C4_1 *entry;

    entry = (entry_index * 0x10) + table->unk_10;
    func_8001E578(entry->unk_0C, entry);
}
