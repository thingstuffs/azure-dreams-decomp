#include "common.h"

extern s32 count_nonzero_word_prefix(s32 *a0, s32 a1);
extern s32 create_callback_pair_default(s32 a0);

/* Allocates a 0x104-byte block, stores its address at the looked-up array index, and returns it. */
s32 allocate_and_append_callback_payload(s32 *values, s32 lookup_key)
{
    s32 index = count_nonzero_word_prefix(values, lookup_key);
    s32 value = create_callback_pair_default(0x104);
    values[index] = value;
    return value;
}
