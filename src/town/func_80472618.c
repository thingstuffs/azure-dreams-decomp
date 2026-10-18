#include "common.h"
void func_8001A418(s32, void *);                 /* extern */

typedef struct S_80472618_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80472618_0;   /* arg0 in apply_signed_value_to_indexed_entry */

typedef struct S_80472618_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80472618_1;

/* Pass the indexed entry and its signed 16-bit value to func_8001A418. */
void apply_signed_value_to_indexed_entry(S_80472618_0 *entry_table, s32 entry_index) {
    S_80472618_1 *entry;

    entry = (entry_index * 0x10) + entry_table->unk_10;
    func_8001A418(entry->unk_0C, entry);
}
