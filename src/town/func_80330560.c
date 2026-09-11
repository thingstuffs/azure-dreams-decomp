#include "common.h"

extern s32 D_80016000[3];
extern s32 D_80016000_reload[3] __asm__("D_80016000");

/* Clears the indexed flag bit unless the index is 1. */
void func_8001AD60(s32 bit_index) {
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 *dst_word;
    s32 *src_word;
    s32 word_offset;
    s32 adjusted_index;
    s32 clear_mask;

    value = 1;
    if (bit_index != value) {
        value = D_80016000[0];

        adjusted_index = bit_index;
        if (bit_index < 0) {
            adjusted_index = bit_index + 31;
        }
        word_offset = (adjusted_index >> 5) * 4;
        value = *(s32 *)(value + 0x18);
        dst_word = (s32 *)(word_offset + value);

        value = D_80016000_reload[0];
        src_word = (s32 *)(word_offset + *(s32 *)(value + 0x18));
        ASM_KEEP(src_word);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        value = bit_index;
        if (bit_index < 0) {
            value = bit_index + 31;
        }
        clear_mask = ~(1 << (bit_index - ((value >> 5) << 5)));
        do {
            *dst_word = clear_mask & *src_word;
        } while (0);
    }
}
