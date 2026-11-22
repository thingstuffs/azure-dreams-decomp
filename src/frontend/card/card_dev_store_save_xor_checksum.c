#include "frontend/card/save_image.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/checksum_trace_data.h"

/* Compute, store, and print the XOR checksum of the game-save work data. */
void card_dev_store_save_xor_checksum(CardDevSaveWork *save) {
    s32 *save_word;
    s32 word;
    s32 check_sum;
    s32 words_left;

    check_sum = 0;
    save_word = save->words;
    words_left = 0x1781;
    do {
        word = *save_word;
        save_word += 1;
        words_left -= 1;
        check_sum ^= word;
    } while (words_left >= 0);
    save->checksum = check_sum;
    printf_8007C040(checksum_trace_format, saved_checksum_label, check_sum);
}
