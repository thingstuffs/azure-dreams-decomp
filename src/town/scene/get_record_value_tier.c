#include "common.h"

s32 town_table_contains_first_byte_b(s32);

/* Return 2 if check 3 succeeds, otherwise return whether check 2 succeeds. */
s32 get_record_value_tier(void) {
    if (town_table_contains_first_byte_b(3) != 0) {
        return 2;
    }
    return town_table_contains_first_byte_b(2) != 0;
}
