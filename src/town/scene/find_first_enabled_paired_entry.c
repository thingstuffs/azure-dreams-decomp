#include "common.h"
#include "town/scene.h"


extern void set_script_flag_bit(s32 bit_index);
extern s32 get_script_flag_mask(s32 flagIndex);
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
        if ((get_script_flag_mask(entry->unk_04) != 0) && (get_script_flag_mask(entry->unk_06)
            == 0)) {
            set_script_flag_bit(entry->unk_06);
            return entry_index;
        }
    }
    return 0;
}
