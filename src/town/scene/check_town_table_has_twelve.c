#include "common.h"
#include "town/scene.h"
#include "town.h"

/* Calls return with town_table_contains_first_byte_c(0xc)! = 0. */
s32 check_town_table_has_twelve(void) { return (town_pair_table_has_first(0xc) != 0); }
