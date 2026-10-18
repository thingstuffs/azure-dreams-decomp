#include "common.h"
void func_80017568(s32, void *);                 /* extern */

typedef struct S_8047E8B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8047E8B4_0;   /* arg0 in build_object_set_and_select_lists_rev_b */

typedef struct S_8047E8B4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8047E8B4_1;

/* Pass the indexed entry and its identifier to func_80017568. */
void build_object_set_and_select_lists_rev_b(S_8047E8B4_0 *entry_table, s32 entry_index) {
    S_8047E8B4_1 *entry;

    entry = (entry_index * 0x10) + entry_table->unk_10;
    func_80017568(entry->unk_0C, entry);
}
