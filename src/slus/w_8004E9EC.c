#include "common.h"

typedef struct PatternSource {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 pad[13];
} PatternSource;

typedef struct Pattern3 {
    s8 b0;
    s8 b1;
    s8 b2;
} Pattern3;

extern PatternSource D_80080B70;

/* Fill from the first zero byte with overlapping patterns; return whether a zero was found. */
s32 func_8004E9EC(u8 *buffer, s32 pair_count)
{
    s32 offset;
    s32 found_zero;
    s32 end_offset;

    found_zero = 0;
    end_offset = pair_count << 1;
    offset = found_zero;
    if (end_offset >= 0) {
        do {
            if (buffer[offset] == 0) {
                s32 fill_end = end_offset;
                found_zero = 1;
                if (offset < fill_end) {
                    do {
                        *(Pattern3 *)(buffer + offset) = *(Pattern3 *)&D_80080B70;
                        offset += 2;
                    } while (offset < fill_end);
                    found_zero = 1;
                }
            }
            offset++;
            end_offset = pair_count << 1;
        } while (end_offset >= offset);
    }
    return found_zero;
}
