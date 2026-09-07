#include "common.h"

extern u8 D_80409290[];

/* Returns whether text matches a record prefix, comparing at most 21 bytes. */
s32 func_80401AA4(s32 count, u8 *text)
{
    s32 record_index;
    s32 matched;
    s32 mismatch;
    u8 *record;
    register u8 *record_pos ASM_REG("$6");
    register u8 *text_pos ASM_REG("$7");
    register u8 *record_end ASM_REG("$10");
    u8 text_byte;
    s32 stack_pad;

    (void)&stack_pad;
    record_index = 0;
    matched = 0;
    if (count > 0) {
        record = D_80409290;
outer:
        mismatch = 0;
        record_pos = record;
        text_pos = text;
        record_end = record + 21;
inner:
        text_byte = *text_pos;
        if (text_byte != 0) {
            if (text_byte != *record_pos++) {
                goto mismatch_found;
            }
            text_pos++;
            if ((long)record_pos < (long)record_end) {
                goto inner;
            }
        }
after:
        if (mismatch != 0) {
            goto next_record;
        }
        matched = 1;
        goto done;

mismatch_found:
        mismatch++;
        goto after;

next_record:
        record_index++;
        record += 40;
        if (record_index < count) {
            goto outer;
        }
    }
done:
    return matched;
}
