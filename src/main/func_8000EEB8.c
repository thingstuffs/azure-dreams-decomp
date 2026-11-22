#include "modules/main_server_ship.h"
#include "common.h"
#include "frontend/card/save_image.h"
#include "main.h"

/* Compute and store the XOR checksum of the buffer's data words. */
void card_boot_store_save_xor_checksum(CardSaveImage *save) {
    s32 *word_ptr;
    s32 word;
    s32 checksum;
    s32 words_left;

    checksum = 0;
    word_ptr = save->data.words;
    words_left = 0x177D;
    do {
        word = *word_ptr;
        word_ptr += 1;
        words_left -= 1;
        checksum ^= word;
    } while (words_left >= 0);
    save->checksum = checksum;
}
