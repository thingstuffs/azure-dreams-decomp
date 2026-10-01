#include "common.h"
#include "shared/record_ptrs.h"

extern s32 D_80016000_reload[3] __asm__("D_80016000");

/* Clears the indexed flag bit unless the index is 1. */
void func_8001AD60(s32 bit_index) {
    s32 value;
    s32 *dst_word;
    s32 *src_word;
    s32 word_index;
    s32 table;
    s32 adjusted_index;
    s32 clear_mask;

    value = 1;
    if (bit_index != value) {
        value = ((s32)D_80016000);

        adjusted_index = bit_index;
        if (bit_index < 0) {
            adjusted_index = bit_index + 31;
        }
        word_index = adjusted_index >> 5;
        table = *(s32 *)(value + 0x18);
        dst_word = (s32 *)(word_index * 4 + table);

        src_word = (s32 *)(*(s32 *)(D_80016000_reload[0] + 0x18) + word_index * 4);

        value = bit_index;
        if (bit_index < 0) {
            value = bit_index + 31;
        }
        clear_mask = ~(1 << (bit_index - ((value >> 5) << 5)));
        *dst_word = clear_mask & *src_word;
    }
}
