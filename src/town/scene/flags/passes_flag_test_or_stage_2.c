#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

/* Check whether the initial query is zero or the secondary value is at least two. */
s32 passes_flag_test_or_stage_2(s32 query_input_a, s32 query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 below_two;

    if (get_flag_test_table_address() != 0) {
        below_two = get_state_record_byte() < 2;
        if (below_two != 0) {
            return 0;
        }
    }
    return 1;
}
