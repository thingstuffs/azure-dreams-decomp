#include "common.h"
#include "town.h"

/* Calls return with town_table_contains_first_byte_c(6)! = 0. */
s32 check_town_table_has_six(void) { return (town_pair_table_has_first(6) != 0); }
