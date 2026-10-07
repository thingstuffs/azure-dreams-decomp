#include "common.h"
#include "shared/record_ptrs.h"


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
        word_index = (adjusted_index / 32);
        table = *(s32 *)(value + 0x18);
        dst_word = (s32 *)(word_index * 4 + table);

        src_word = (s32 *)(*(s32 *)((s32)D_80016000 + 0x18) + word_index * 4);

        value = bit_index;
        clear_mask = ~(1 << (bit_index % 32));
        *dst_word = clear_mask & *src_word;
    }
}
