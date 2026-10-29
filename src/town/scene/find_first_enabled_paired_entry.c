#include "common.h"
#include "town/scene.h"


extern void func_8001E578(s32 bit_index);
extern s32 func_8001E670(s32 flagIndex);
extern u8 town_selection_records[96];

typedef struct S_8001A360_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_8001A360_0;

/* Process the first entry whose paired checks pass and fail, returning its index or zero. */
s32 find_first_enabled_paired_entry(void) {
    s32 entry_index;
    S_8001A360_0 *entry;
    u8 *table_base;

    table_base = town_selection_records;
    for (entry_index = 1; entry_index < 8; entry_index++) {
        entry = (S_8001A360_0 *)(table_base + entry_index * 12);
        if ((func_8001E670(entry->unk_04) != 0) && (func_8001E670(entry->unk_06)
            == 0)) {
            func_8001E578(entry->unk_06);
            return entry_index;
        }
    }
    return 0;
}
