#include "common.h"
#include "engine/item.h"
#include "engine/util.h"

/* Passes both pointers through flag_removal_when_value_zero and decrement_and_flag_removal_if_nonzero in order. */
void mark_and_release_record_pair(void *first_ptr, void *second_ptr)
{
    flag_removal_when_value_zero(first_ptr, second_ptr);
    decrement_and_flag_removal_if_nonzero(first_ptr, second_ptr);
}
