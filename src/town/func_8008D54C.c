#include "common.h"

/* Copy words backward from the supplied byte offset in the source and destination. */
void func_8008ACAC(s32 dest_addr, s32 src_addr, s32 byte_count) {
    s32 *dest_word;
    s32 *src_word;
    s32 word;
    s32 adjusted_bytes;
    s32 words_left;

    adjusted_bytes = byte_count;
    dest_word = dest_addr + adjusted_bytes;
    src_word = src_addr + adjusted_bytes;
    if (adjusted_bytes < 0) {
        adjusted_bytes += 3;
    }
    words_left = adjusted_bytes >> 2;
    if (words_left > 0) {
        do {
            word = *src_word;
            src_word -= 1;
            words_left -= 1;
            *dest_word = word;
            dest_word -= 1;
        } while (words_left > 0);
    }
}
