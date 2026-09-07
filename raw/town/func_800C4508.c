#include "common.h"

s32 func_800C1C68(s32 arg0, s16 **arg1)
{
    s16 **outer;
    s16 *ranges;
    s16 *pair;
    register s32 outer_index ASM_REG("$8");
    register s32 return_value ASM_REG("$2");
    s32 result;
    s32 pair_offset;
    s32 outer_sentinel;
    s32 inner_sentinel;

    if (*arg1 == 0) {
        goto not_found;
    }

    outer_index = 0;
    ASM_KEEP(outer_index);
    outer_sentinel = -1;
    outer = arg1;
    ranges = *(s16 * volatile *)outer;

outer_loop:
    if (*ranges != outer_sentinel) {
        result = outer_index + 1;
        inner_sentinel = -1;
        pair_offset = 0;

inner_loop:
        ranges = *(s16 * volatile *)outer;
        pair = (s16 *)(pair_offset + (s32)ranges);
        if (arg0 < pair[0]) {
            goto advance;
        }
        if (pair[1] < arg0) {
            goto advance;
        }
        return_value = result;
        goto done;

advance:
        ranges = arg1[outer_index];
        pair_offset += 4;
        return_value = pair_offset + (s32)ranges;
        ASM_KEEP(return_value);
        return_value = *(s16 *)return_value;
        ASM_KEEP(return_value);
        if (return_value != inner_sentinel) {
            goto inner_loop;
        }
    }

    outer++;
    ranges = *outer;
    outer_index++;
    if (ranges != 0) {
        goto outer_loop;
    }

not_found:
    return_value = 0;
done:
    ASM_KEEP(return_value);
    return return_value;
}

/* MECHANISM: Frameless sentinel-table search with one shared return.
   Fresh reads split the $v0 base from the $v1 comparison pair; the sentinel
   probe reuses the short-lived pinned return register for address and load.
   Guarded $t0 induction/$v0 return roles produce the shared retail epilogue. */
