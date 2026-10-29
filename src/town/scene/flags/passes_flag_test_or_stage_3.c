#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

/* Check whether the initial query is zero or the secondary value is at least three. */
s32 passes_flag_test_or_stage_3(s32 query_input_a, s32 query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 less_than_three;

    if (get_flag_test_table_address() != 0) {
        less_than_three = get_state_record_byte() < 3;
        if (less_than_three != 0) {
            return 0;
        }
    }
    return 1;
}
