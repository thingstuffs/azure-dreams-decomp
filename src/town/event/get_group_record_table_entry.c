#include "common.h"

#define FIELD_U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

#include "engine/object/test_resident_bitmap_bit_api.h"
extern s32 find_sentinel_table_value_index(s32 target_value);
extern s32 classify_item_check_result();
s32 classify_listed_entry_type(u8 *);
s32 filter_entry_by_kind(s32, u8 *);

extern u8 D_8006BC7A;
extern s32 *D_800D1038[];

/* Returns the table entry for a group and record, with a special-case override. */
s32 get_group_record_table_entry(s32 group_id, void *record) {
    s32 table_index;
    register s32 **table_slot;
    s32 **tables;
    s32 row_index;
    s32 column;
    s32 result;

    table_index = find_sentinel_table_value_index(group_id);
    if ((table_index != -1) && (filter_entry_by_kind(group_id, record) != 0)) {
        if ((FIELD_U8(record, 1) == 13) && (group_id == 9)) {
            if (FIELD_U8(record, 0) == 3) {
                if (test_resident_bitmap_bit(0x12CB) != 0) {
                    u8 *special_result;

                    special_result = (u8 *)&D_8006BC7A;
                    return (s32)special_result;
                }
                return 0;
            } else {
                column = 3;
            }
        } else {
            column = classify_listed_entry_type(record);
        }
        row_index = classify_item_check_result(table_index);
        tables = D_800D1038;
        table_slot = (s32 **)((table_index * 4) + (s32)tables);
        result = (table_slot[0] + (row_index * 4))[column];
        return result;
    }
    return 0;
}
