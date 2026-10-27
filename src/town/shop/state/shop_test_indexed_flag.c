#include "common.h"
#include "town/shop/state.h"

extern s32 *shop_indexed_flag_words[];

/* Tests an indexed flag, treating indices zero and one as constant results. */
s32 test_linked_flag(s32 flag_index)
{
    s32 unit_bit;
    s32 value;
    s32 *flag_word;
    s32 adjusted_index;
    unsigned long word_address;

    unit_bit = 1;
    if (flag_index != 0) {
        if (flag_index != unit_bit) {
            adjusted_index = flag_index;
            value = (adjusted_index / 32);
            word_address = value << 2;
            value <<= 5;
            word_address += (unsigned long)shop_indexed_flag_words[0];
            value = flag_index - value;
            value = unit_bit << value;
            flag_word = (s32 *)word_address;
            return value & *flag_word;
        } else {
            s32 zero = 0;
            return zero + 1;
        }
    } else {
        s32 zero = 0;
        return zero;
    }
}
