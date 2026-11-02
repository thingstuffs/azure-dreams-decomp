#include "common.h"

extern s32 town_table_contains_first_byte_b(s32);
/* Calls return with record_value_table_contains_first_byte_d(1)= = 0. */
s32 invoke_callback_and_set_shared_pointer(void) { return (town_table_contains_first_byte_b(1) == 0); }
