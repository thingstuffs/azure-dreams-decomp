#include "common.h"

extern s32 count_nonzero_word_prefix(s32 *a0, s32 a1);
extern s32 alloc_buffer_array(s32 *a0, s32 a1);

/* Skip live entries and allocate size / 21 + 1 slots, returning their pointer or NULL on failure. */
s32 *allocate_entry_slots(s32 *entries, u32 size, s32 skip_limit)
{
    s32 skip_count;
    s32 *slots;

    skip_count = count_nonzero_word_prefix(entries, skip_limit);
    slots = entries + skip_count;
    if (!alloc_buffer_array(slots, size / 21 + 1)) {
        slots = 0;
    }
    return slots;
}
