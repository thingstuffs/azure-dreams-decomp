/* Indexed entry remove and its file-private helper. */
#include "common.h"
#include "m2c_compat.h"
static void clear_indexed_table_flag();
/* extern */

typedef struct S_800B2190_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2190_0;
typedef struct S_800B2190_1 {
    s32 unk_00;
} S_800B2190_1;
typedef struct S_800B2190_2 {
    void * unk_00;
    void * unk_04;
} S_800B2190_2;

static void clear_indexed_table_flag(void *record) {
    u8 *page = (u8 *)0x80010000;
    page[((((u8 *)record)[3] & 0x1F) * 0x54) + 0x303] = 0;
}

void remove_selected_entry_from_list(s32 list_addr, s32 index) {
    s32 slot_offset;
    void **slot;
    S_800B2190_0 *entry;

    slot_offset = index * 4;
    slot = list_addr + slot_offset;
    entry = *slot;
    if (entry->unk_01 == 0x13) {
        clear_indexed_table_flag(entry);
    }
    ((S_800B2190_1 *)(*slot))->unk_00 = 0;
    if (*slot != NULL) {
        do {
            ((S_800B2190_2 *)slot)->unk_00 = ((S_800B2190_2 *)slot)->unk_04;
            slot = (void **)((s8 *)((void **)((s8 *)slot + 4)));
        } while (*slot != NULL);
    }
}
