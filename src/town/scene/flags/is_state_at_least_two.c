#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

/* Return whether the state byte is at least two; the table lookup always returns an address. */
s32 is_state_at_least_two(void *query_input_a, void *query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 below_two;

    if (get_flag_test_table_address(query_input_a, query_input_b, query_input_c, query_input_d) != 0) {
        below_two = get_state_record_byte() < 2;
        if (below_two != 0) {
            return 0;
        }
    }
    return 1;
}
