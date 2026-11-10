#include "common.h"
#include "town.h"


/* Calls contains_record_value_in_byte_0 with selector 0x10. */
void query_state_with_selector_10(void) {
    town_table_contains_first_byte_b(0x10);
}
