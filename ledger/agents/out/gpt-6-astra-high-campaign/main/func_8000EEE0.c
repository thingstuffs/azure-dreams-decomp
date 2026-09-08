#include "common.h"

/* Checks the stored checksum against the XOR of 6014 data words. */
s32 func_80021EE0(void *save_data) {
    s32 *data_word;
    s32 checksum;
    s32 word_index;

    checksum = 0;
    data_word = (s32 *) ((u8 *) save_data + 0x208);
    word_index = checksum;
    do {
        checksum ^= *data_word++;
        word_index += 1;
    } while (word_index < 6014);
    return (*(s32 *) ((u8 *) save_data + 0x204) ^ checksum) == 0;
}
