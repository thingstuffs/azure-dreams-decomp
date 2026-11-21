#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/checksum_trace_data.h"

/* Compute, store, and print the XOR checksum of the game-save work data. */
void card_dev_store_save_xor_checksum(void *gsw) {
    u32 *save_word;
    u32 word;
    u32 check_sum;
    s32 words_left;

    check_sum = 0;
    save_word = (u32 *)((u8 *)gsw + 0x208);
    words_left = 0x1781;
    do {
        word = *save_word;
        save_word += 1;
        words_left -= 1;
        check_sum ^= word;
    } while (words_left >= 0);
    *(u32 *)((u8 *)gsw + 0x204) = check_sum;
    printf_8007C040(checksum_trace_format, saved_checksum_label, check_sum);
}
