#include "common.h"

extern s32 *D_807030A4[];

/* Clear the indexed flag bit unless the index is one. */
void func_807026C0(s32 bit_index) {
    register s32 input ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 *flag_word;
    s32 rounded_index;
    s32 bit_mask;
    unsigned long word_address;

    input = bit_index;
    if (input != 1) {
        rounded_index = input;
        if (input < 0) {
            rounded_index = input + 31;
        }
        bit_mask = rounded_index >> 5;
        word_address = bit_mask << 2;
        bit_mask <<= 5;
        bit_mask = input - bit_mask;
        bit_mask = 1 << bit_mask;
        word_address += (unsigned long)D_807030A4[0];
        flag_word = (s32 *)word_address;
        bit_mask = ~bit_mask;
        bit_mask &= *flag_word;
        *flag_word = bit_mask;
    }
}
