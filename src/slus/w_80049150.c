#include "common.h"

extern s32 func_80048F8C(s32 *a0, s32 a1);
extern s32 allocBufferArray(s32 *a0, s32 a1);

/* Advance past the first `a2` (or fewer, if a zero-entry is hit sooner) live
 * entries of the array at a0, then attempt to reserve/allocate a1/21 + 1
 * slots starting there via allocBufferArray. Returns the advanced pointer on
 * success, or NULL on failure. */
s32 *func_80049150(s32 *a0, u32 a1, s32 a2)
{
    s32 count;
    s32 *p;

    count = func_80048F8C(a0, a2);
    p = a0 + count;
    if (!allocBufferArray(p, a1 / 21 + 1)) {
        p = 0;
    }
    return p;
}
