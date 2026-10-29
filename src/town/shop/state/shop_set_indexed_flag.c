#include "common.h"
#include "town/shop/state.h"

extern s32 *shop_indexed_flag_words[];

/* Set the indexed flag bit unless the index is zero. */
void set_linked_flag(s32 bit_index) {
    if (bit_index != 0) {
        shop_indexed_flag_words[0][bit_index / 32] |= (1 << (bit_index % 32));
    }
}
