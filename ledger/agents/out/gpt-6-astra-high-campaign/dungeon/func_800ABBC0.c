#include "common.h"

/* Offset the two coordinate bytes in each record through the end marker. */
void func_800B1320(u8 *record, s32 x_offset, s32 y_offset) {
    u8 *record_y;

    record_y = record + 3;
loop:
        record_y[-1] += x_offset;
        record_y[0] += y_offset;
        if (*(s8 *)record < 0) {
            goto done;
        }
        record_y += 0xC;
        record += 0xC;
        goto loop;
done:
    ;
}
