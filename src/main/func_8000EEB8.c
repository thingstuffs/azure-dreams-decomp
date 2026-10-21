#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"
#include "main.h"

typedef struct func_8000EEB8_S_80021EB8_0 {
    u8 pad_00[0x204];
    s32 unk_204;
} func_8000EEB8_S_80021EB8_0;   /* arg0 in card_boot_store_save_xor_checksum */

/* Compute and store the XOR checksum of the buffer's data words. */
void card_boot_store_save_xor_checksum(void *buffer) {
    s32 *word_ptr;
    s32 word;
    s32 checksum;
    s32 words_left;

    checksum = 0;
    word_ptr = buffer + 0x208;
    words_left = 0x177D;
    do {
        word = *word_ptr;
        word_ptr += 1;
        words_left -= 1;
        checksum ^= word;
    } while (words_left >= 0);
    ((func_8000EEB8_S_80021EB8_0 *)buffer)->unk_204 = checksum;
}
