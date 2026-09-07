#include "common.h"

extern u8 D_80028570[];

/* Return whether any record matches text through its terminator or the first 21 bytes. */
s32 func_80021A04(s32 count, u8 *text)
{
    s32 record_index;
    s32 found;
    u8 *records;

    record_index = 0;
    found = record_index;
    records = D_80028570;
    if (count > 0) {
        u8 *record;

        record = records;
        do {
            s32 mismatch;
            s32 char_index;

            mismatch = 0;
            char_index = mismatch;
            do {
                u8 character;

                character = text[char_index];
                if (character == 0) {
                    break;
                }
                if (character != record[char_index]) {
                    mismatch++;
                    break;
                }
                char_index++;
            } while (char_index < 0x15);
            if (mismatch == 0) {
                found = 1;
                break;
            }
            record_index++;
            record += 0x28;
        } while (record_index < count);
    }
    return found;
}
