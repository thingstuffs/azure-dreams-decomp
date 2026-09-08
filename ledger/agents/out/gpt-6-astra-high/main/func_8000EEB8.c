#include "common.h"
#include "m2c_compat.h"

typedef struct S_80021EB8_0 {
    u8 pad_00[0x204];
    s32 unk_204;
} S_80021EB8_0;   /* arg0 in func_80021EB8 */

/* Compute and store the XOR checksum of the buffer's data words. */
void func_80021EB8(void *buffer) {
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
    ((S_80021EB8_0 *)buffer)->unk_204 = checksum;
}
