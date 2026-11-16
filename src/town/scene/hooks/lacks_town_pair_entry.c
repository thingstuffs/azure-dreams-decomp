#include "common.h"
#include "town.h"

/* Calls return with record_value_table_contains_first_byte_d(1)= = 0. */
s32 lacks_town_pair_entry(void) { return (town_pair_table_has_first(1) == 0); }
