#include "common.h"

extern s32 func_80048F8C(s32 *a0, s32 a1);
extern s32 allocBufferArray(s32 *a0, s32 a1);

/* Skip live entries and allocate size / 21 + 1 slots, returning their pointer or NULL on failure. */
s32 *func_80049150(s32 *entries, u32 size, s32 skip_limit)
{
    s32 skip_count;
    s32 *slots;

    skip_count = func_80048F8C(entries, skip_limit);
    slots = entries + skip_count;
    if (!allocBufferArray(slots, size / 21 + 1)) {
        slots = 0;
    }
    return slots;
}
