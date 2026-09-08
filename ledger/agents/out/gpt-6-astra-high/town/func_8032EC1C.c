#include "common.h"

/* Copies count 32-bit words from src to dst. */
void func_8001941C(s32 *dst, s32 *src, s32 count) {
    s32 *dst_word;
    s32 *src_word;
    s32 remaining;

    dst_word = dst;
    src_word = src;
    remaining = count;
    if (remaining != 0) {
        do {
            *dst_word = *src_word;
            src_word++;
            remaining--;
            dst_word++;
        } while (remaining != 0);
    }
}
