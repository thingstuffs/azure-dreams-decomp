#include "common.h"

extern u8 D_80028570[];

s32 func_80021A04(s32 count, u8 *text)
{
    s32 record_index;
    s32 result;
    u8 *records;

    record_index = 0;
    result = record_index;
    records = D_80028570;
    if (count > 0) {
        u8 *record;

        record = records;
        do {
            s32 mismatch;
            s32 index;

            mismatch = 0;
            index = mismatch;
            do {
                u8 value;

                value = text[index];
                if (value == 0) {
                    break;
                }
                if (value != record[index]) {
                    mismatch++;
                    break;
                }
                index++;
            } while (index < 0x15);
            if (mismatch == 0) {
                result = 1;
                break;
            }
            record_index++;
            record += 0x28;
        } while (record_index < count);
    }
    return result;
}
