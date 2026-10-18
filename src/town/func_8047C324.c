#include "common.h"
void func_800197D8(s32, void *);                 /* extern */

typedef struct S_8047C324_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8047C324_0;   /* arg0 in pass_entry_identifier_to_handler */

typedef struct S_8047C324_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8047C324_1;

/* Pass the indexed entry and its identifier to func_800197D8. */
void pass_entry_identifier_to_handler(S_8047C324_0 *entry_table, s32 entry_index) {
    S_8047C324_1 *entry;

    entry = (entry_index * 0x10) + entry_table->unk_10;
    func_800197D8(entry->unk_0C, entry);
}
