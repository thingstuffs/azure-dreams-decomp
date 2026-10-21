/* inferred-strong G00589: entry_kind_filters_g00589; joins CL:town/func_800AC118,CL:town/func_800AC278,CL:town/func_800AC2D8,CL:town/func_800AC37C; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC278, CL:town/func_800AC2D8, CL:town/func_800AC37C. */
#include "town/event/entry_kind_filters_g00589.h"

/* Classifies listed entry types by two value thresholds, returning 3 for unlisted types. */
s32 classify_listed_entry_type(u8 *entry) {
    s32 type_index;
    s32 entry_value;

    if (D_800D1074[0] != -1) {
        type_index = 0;
        do {
            if (D_800D1074[type_index] == entry[1]) {
                entry_value = get_item_sell_money(entry);
                if (entry_value < D_800D1080[0]) {
                    return 0;
                }
                if (entry_value < D_800D1080[1]) {
                    return 1;
                }
                return 2;
            }
            type_index++;
        } while (D_800D1074[type_index] != -1);
    }

    return 3;
}

/* Check whether the entry passes its kind-specific value filter. */
s32 filter_entry_by_kind(s32 unused, u8 *entry) {
    s32 k = entry[1];

    if (k == 13) {
        if (entry[0] == 4) {
            return 1;
        }
        if (entry[0] == 3) {
            return 1;
        }
        return 0;
    }
    if (k == 1) {
        return entry[0] != 8;
    }
    return 1;
}

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
                if (test_resident_bitmap_bit(F_takoyaki_morau) != 0) {
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
