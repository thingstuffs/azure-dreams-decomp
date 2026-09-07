#include "common.h"

extern u8 D_80409290[];

s32 func_80401AA4(s32 count, u8 *text)
{
    s32 index;
    s32 result;
    s32 mismatch;
    u8 *record;
    register u8 *record_pos ASM_REG("$6");
    register u8 *text_pos ASM_REG("$7");
    register u8 *record_end ASM_REG("$10");
    u8 byte;
    s32 pad;

    (void)&pad;
    index = 0;
    result = 0;
    if (count > 0) {
        record = D_80409290;
outer:
        mismatch = 0;
        record_pos = record;
        text_pos = text;
        record_end = record + 21;
inner:
        byte = *text_pos;
        if (byte != 0) {
            if (byte != *record_pos++) {
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
        result = 1;
        goto done;

mismatch_found:
        mismatch++;
        goto after;

next_record:
        index++;
        record += 40;
        if (index < count) {
            goto outer;
        }
    }
done:
    return result;
}
