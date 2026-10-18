#include "common.h"

extern s32 test_selected_resident_flag(s32 table_index);
extern s32 get_query_result_for_check_type(s32 check_type);
extern s32 check_slot_threshold_or_fallback(s32 slot);

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
