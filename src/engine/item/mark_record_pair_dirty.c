#include "common.h"
#include "engine/item.h"
#include "engine/util.h"

/* Passes both pointers through mark_record_if_indirect_value_zero and decrement_and_flag_removal_if_nonzero in order. */
void mark_record_pair_dirty(void *first_ptr, void *second_ptr)
{
    mark_record_if_indirect_value_zero(first_ptr, second_ptr);
    decrement_and_flag_removal_if_nonzero(first_ptr, second_ptr);
}
