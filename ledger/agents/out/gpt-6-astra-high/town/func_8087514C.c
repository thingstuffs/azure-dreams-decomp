#include "common.h"
#include "m2c_compat.h"

extern u8 D_80700000[];

/* Clears six indexed bits in the shared bitmap. */
void func_8087514C(void) {
    register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
    s32 slot;
    s32 one_bit;
    s16 *bit_index_ptr;

    slot = zero | 1;
    ASM_UNDEF(zero);   /* MATCH pin: load-bearing for the whole function shape */
    one_bit = zero | 1;
    bit_index_ptr = (s16 *)(D_80700000 + 0xBAE);
    do {
        register s32 bit_index ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        register s32 bit_value ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
        register s32 slot_offset ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
        s32 word_addr;
        s32 first_word;
        s32 second_word;
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
            s32 bitmap_base;
            bitmap_base = 0x80700000;
            bitmap_base = *(s32 *)(bitmap_base + 0x1968);
            bit_value = one_bit << bit_value;
            word_addr = word_addr + bitmap_base;
            word_ptr = (s32 *)word_addr;
        }
        first_word = *word_ptr;
        bit_value = ~bit_value;
        bit_value = bit_value & first_word;
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
            s32 bitmap_base;
            bitmap_base = 0x80700000;
            bitmap_base = *(s32 *)(bitmap_base + 0x1968);
            bit_value = one_bit << bit_value;
            word_addr = word_addr + bitmap_base;
            word_ptr = (s32 *)word_addr;
        }
        second_word = *word_ptr;
        ASM_KEEP(second_word);   /* MATCH pin: load-bearing for the whole function shape */
        bit_value = ~bit_value;
        bit_value = bit_value & second_word;
        *word_ptr = bit_value;
        bit_index_ptr += 1;
    } while (slot < 4);
}
