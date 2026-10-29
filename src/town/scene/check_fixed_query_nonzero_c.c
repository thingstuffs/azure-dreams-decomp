#include "common.h"
#include "town/scene.h"

extern s32 town_table_contains_first_byte_c(s32);
/* Calls return with town_table_contains_first_byte_c(0xc)! = 0. */
s32 check_fixed_query_0xc_nonzero(void) { return (town_table_contains_first_byte_c(0xc) != 0); }
