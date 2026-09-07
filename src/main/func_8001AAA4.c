#include "common.h"

extern u8 D_80409290[];
extern s32 func_80401AF8(s32 count, u8 *text, u8 *record_pos, u8 *text_pos);
extern s32 func_80401B20(s32 count, u8 *text, u8 *record_pos, u8 *text_pos);

s32 func_8001AAA4(s32 count, u8 *text)
{
    s32 index = 0;
    s32 result = 0;
    s32 mismatch;
    u8 *record;
    u8 *record_pos;
    u8 *text_pos;
    u8 *record_end;
    u8 byte;

    if (count > 0) {
        record = D_80409290;
outer:
        mismatch = 0;
        result++;
        result--;
        record_pos = record;
        text_pos = text;
        record_end = record + 21;
        record_end++;
        record_end--;
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
        if (mismatch != 0) {
            goto next_record;
        }
        result = 1;
        return func_80401B20(count, text, record_pos, text_pos);

mismatch_found:
        mismatch++;
        return func_80401AF8(count, text, record_pos, text_pos);

next_record:
        index++;
        record += 40;
        if (index < count) {
            goto outer;
        }
    }
    return result;
}
