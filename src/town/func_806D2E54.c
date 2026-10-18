#include "common.h"

extern s32 select_data_array_based_flag(s16);

/* Check whether every flag in the zero-terminated list is set. */
s32 check_all_flag_test_bits(s16 *flag_ids) {
    s16 *flag_id = flag_ids;

    while (*flag_id != 0) {
        if (select_data_array_based_flag(*(u16 *)flag_id) == 0) {
            break;
        }
        flag_id++;
    }

    return *flag_id == 0;
}
