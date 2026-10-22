/* Display-spacing table selection and cached byte-count offsets. */
#include "common.h"

extern u8 indexed_count_byte_table[];
u8 indexed_byte_table_count_plus_five = 0;
u8 indexed_byte_table_double_count_plus_five = 0;

#include "../build/partition_sources/code2__table_counters_b1b_b1c.c"
