#include "common.h"
#include "m2c_compat.h"

extern u8 D_80700000[];

static __inline__ s32 rounded_bit_index(s32 bit_index) {
    s32 rounded_index = bit_index;
    if (bit_index < 0) rounded_index = bit_index + 31;
    return rounded_index;
}

static __inline__ void clear_indexed_bit(s32 bitmap, s32 bit_index, s32 rounded_index, s32 one_bit) {
    s32 word_addr;
    s32 bit_value;
    s32 bitmap_word;
    s32 *word_ptr;
    rounded_index >>= 5;
    word_addr = rounded_index << 2;
    bit_value = bit_index - (rounded_index << 5);
    bitmap = *(s32 *)(bitmap + 0x1968);
    word_ptr = (s32 *)(word_addr + (s32)bitmap);
    bitmap_word = *word_ptr;
    *word_ptr = ~(one_bit << bit_value) & bitmap_word;
}

/* Clears six indexed bits in the shared bitmap. */
void func_8087514C(void) {
    s32 slot = 1;
    s32 one_bit = 1;
    s16 *bit_index_ptr = (s16 *)(D_80700000 + 0xBAE);
    do {
        s32 slot_offset = 0;
        s32 bit_index;
        s32 rounded_index;
        slot_offset = slot << 1;
        bit_index = *bit_index_ptr;
        rounded_index = rounded_bit_index(bit_index);
        clear_indexed_bit(0x80700000, bit_index, rounded_index, one_bit);
        bit_index = *(s16 *)(D_80700000 + slot_offset + 0xBA4);
        rounded_index = rounded_bit_index(bit_index);
        slot += 1;
        bit_index_ptr += 1;
        clear_indexed_bit(0x80700000, bit_index, rounded_index, one_bit);
    } while (slot < 4);
}
