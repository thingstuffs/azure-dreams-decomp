#include "common.h"

extern s32 record_value_table_contains_first_byte_d(s32);
s32 invoke_callback_and_set_shared_pointer(void) { return (record_value_table_contains_first_byte_d(1) == 0); }
