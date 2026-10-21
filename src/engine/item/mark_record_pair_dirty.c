#include "common.h"
#include "engine/item.h"
#include "engine/util.h"

/* Passes both pointers through mark_record_if_indirect_value_zero and table_handle_decrements_counter_sets_preceding_halfword_global_flag_bit_hex_8000_remains in order. */
void mark_record_pair_dirty(void *first_ptr, void *second_ptr)
{
    mark_record_if_indirect_value_zero(first_ptr, second_ptr);
    table_handle_decrements_counter_sets_preceding_halfword_global_flag_bit_hex_8000_remains(first_ptr, second_ptr);
}
