#include "common.h"

/* Copies words backward from the given byte offset in two buffers. */
void func_8008ACAC(s32 dest_addr, s32 src_addr, s32 byte_count) {
    s32 *dest_word;
    s32 *src_word;
    s32 word;
    s32 byte_offset;
    s32 words_left;

    byte_offset = byte_count;
    dest_word = (s32 *)(dest_addr + byte_offset);
    src_word = (s32 *)(src_addr + byte_offset);
    if (byte_offset < 0) {
        byte_offset += 3;
    }
    words_left = byte_offset >> 2;
    if (words_left > 0) {
        do {
            word = *src_word;
            src_word--;
            words_left--;
            *dest_word = word;
            dest_word--;
        } while (words_left > 0);
    }
}
