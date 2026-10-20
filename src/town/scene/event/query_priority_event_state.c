#include "common.h"

extern s32 record_value_table_contains_first_byte(s32);

/* Return 2 when check 3 passes, otherwise return whether check 2 passes. */
s32 query_priority_event_state(void) {
    if (record_value_table_contains_first_byte(3) != 0) {
        return 2;
    }
    return record_value_table_contains_first_byte(2) != 0;
}
