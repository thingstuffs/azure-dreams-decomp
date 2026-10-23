#include "common.h"

extern s32 *shop_indexed_flag_words[];

/* Clear the indexed flag bit unless the index is one. */
void clear_linked_flag(s32 bit_index) {
    if (bit_index != 1) {
        shop_indexed_flag_words[0][bit_index / 32] &= ~(1 << (bit_index % 32));
    }
}
