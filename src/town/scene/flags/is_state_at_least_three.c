#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"

/* Return whether the state byte is at least three; the table lookup always returns an address. */
s32 is_state_at_least_three(void *query_input_a, void *query_input_b, s32 query_input_c, s32 query_input_d) {
    s32 less_than_three;

    if (get_flag_test_table_address(query_input_a, query_input_b, query_input_c, query_input_d) != 0) {
        less_than_three = get_state_record_byte() < 3;
        if (less_than_three != 0) {
            return 0;
        }
    }
    return 1;
}
