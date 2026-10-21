/* inferred-strong G00588: item_query_checks_g00588; joins CL:town/func_800AC118,CL:town/func_800AC164,CL:town/func_800AC198,CL:town/func_800AC210,PD:town/engine:800D1054; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, PD:town/engine:800D1054. */
#include "town/event/item_query_checks_g00588.h"

/* Returns the matching index in the sentinel-terminated table, or -1. */
s32 find_sentinel_table_value_index(s32 target_value) {
    s32 i = 0;

    while (D_800D1054[i] != -1) {
        if (D_800D1054[i] == target_value) {
            return i;
        }
        i++;
    }
    return -1;
}

/* Passes the selected table entry to test_resident_bitmap_bit. */
s32 test_selected_resident_flag(s32 table_index) {
    test_resident_bitmap_bit(D_800D1064[table_index]);
}

/* Returns the selected query result, testing for zero for check type 3. */
s32 get_query_result_for_check_type(s32 check_type)
{
    switch (check_type) {
    case 0:
        return test_resident_bitmap_bit(Fp_niko_kenkatyu);
    case 2:
        return test_resident_bitmap_bit(Fp_far_kenkatyu);
    case 3:
        return test_resident_bitmap_bit(F_sbs07_pad03) == 0;
    default:
        return 0;
    }
}

/* Checks whether a slot's indexed value is at least three or slot three passes the helper check. */
s32 check_slot_threshold_or_fallback(s32 slot) {
    s16 *entry_indices;
    u8 *data_page;
    s32 entry_index;

    entry_indices = D_800D1054;
    entry_index = entry_indices[slot];
    data_page = (u8 *) 0x80010000;
    if (data_page[(entry_index * 4) + 0x35C4] >= 3U) {
        return 1;
    }
    if (slot == 3) {
        return test_resident_bitmap_bit(F_sbs07_pad04) == 0;
    }
    return 0;
}

s32 classify_item_check_result(s32 input, s32 check_value) {
    s32 result;

    if (test_selected_resident_flag(input) != 0) {
        return 3;
    }
    if (get_query_result_for_check_type(input) != 0) {
        return 0;
    }
    result = check_slot_threshold_or_fallback(input);
    if (result != 0) {
        return 2;
    }
    return 1;
}
