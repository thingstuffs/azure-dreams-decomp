#include "common.h"
#include "m2c_compat.h"

extern u8 D_80700000[];

/* Clears six indexed bits in the shared bitmap. */
void func_8087514C(void) {
    s32 slot;
    s32 one_bit;
    s16 *bit_index_ptr;

    slot = 1;
    one_bit = 1;
    bit_index_ptr = (s16 *)(D_80700000 + 0xBAE);
    do {
        register s32 bit_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 bit_value;
        s32 slot_offset;
        s32 word_addr;
        s32 bitmap_word;
        s32 *word_ptr;

        bit_index = *bit_index_ptr;
        slot_offset = slot << 1;
        bit_value = bit_index;
        if (bit_index < 0) {
            bit_value = bit_index + 0x1F;
        }
        bit_value >>= 5;
        word_addr = bit_value << 2;
        bit_value = bit_index - (bit_value << 5);
        {
            bitmap_word = 0x80700000;
            bitmap_word = *(s32 *)(bitmap_word + 0x1968);
            bit_value = one_bit << bit_value;
            word_addr = word_addr + bitmap_word;
            word_ptr = (s32 *)word_addr;
        }
        bitmap_word = *word_ptr;
        bit_value = ~bit_value;
        bit_value = bit_value & bitmap_word;
        *word_ptr = bit_value;

        bit_index = *(s16 *)(D_80700000 + slot_offset + 0xBA4);
        bit_value = bit_index;
        if (bit_index < 0) {
            bit_value = bit_index + 0x1F;
        }
        slot += 1;
        bit_value >>= 5;
        word_addr = bit_value << 2;
        bit_value = bit_index - (bit_value << 5);
        {
            bitmap_word = 0x80700000;
            bitmap_word = *(s32 *)(bitmap_word + 0x1968);
            bit_value = one_bit << bit_value;
            word_addr = word_addr + bitmap_word;
            word_ptr = (s32 *)word_addr;
        }
        bitmap_word = *word_ptr;
        bit_value = ~bit_value;
        bit_value = bit_value & bitmap_word;
        *word_ptr = bit_value;
        bit_index_ptr += 1;
    } while (slot < 4);
}
