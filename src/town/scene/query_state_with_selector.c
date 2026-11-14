#include "common.h"
#include "town.h"


/* Calls contains_record_value_in_byte_0 with selector 0x10. */
void query_state_with_selector_10(void) {
    town_pair_table_has_first(0x10);
}
