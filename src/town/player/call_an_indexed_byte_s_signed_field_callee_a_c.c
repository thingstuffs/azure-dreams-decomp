#include "common.h"

extern void get_second_word_indexed_entry_in_s_nested_table(void *, u8, s8, s32);

/* Passes an indexed byte and the object's signed field to get_second_word_indexed_entry_in_s_nested_table. */
void call_an_indexed_byte_s_signed_field_callee_80096_a_5_c(void *object, u8 *values, s32 index) {
    get_second_word_indexed_entry_in_s_nested_table(object, values[index], ((s8 *)object)[4], 0);
}
